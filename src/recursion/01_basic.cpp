// =============================================================================
// Number Hunt - jogo de adivinhar números para o cmd.exe
//
// Compilar (MinGW / g++):  g++ -std=c++17 -O2 -o numberhunt.exe main.cpp
// Compilar (MSVC):         cl /std:c++17 /EHsc /utf-8 main.cpp
//
// Estrutura do arquivo:
//   1. Regras e constantes
//   2. Console   (cores, limpar tela, esperar tecla - única parte com WinAPI)
//   3. Input     (leitura e validação de entradas com std::getline)
//   4. Random    (abstração sobre <random>)
//   5. Pontuação (cálculo e ranking salvo em arquivo)
//   6. Jogadores (humano e CPU) e a partida
//   7. Aplicação (telas e menu)
// =============================================================================

#include <algorithm>
#include <charconv>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <conio.h>
#include <windows.h>
#endif

// =============================================================================
// 1. Regras e constantes
// =============================================================================

namespace rules
{
    constexpr int kMinNumber = 1;
    constexpr int kMaxNumber = 1000;
    constexpr std::size_t kMaxNameLength = 6;
    constexpr std::size_t kTopCount = 10;

    // Pontuação: até 700 pontos pelas tentativas + até 300 pelo tempo (máx. 1000).
    // Cada tentativa extra custa 35 pontos e cada segundo custa 3 pontos.
    // Uma busca binária perfeita acerta em no máximo 10 tentativas.
    constexpr int kMaxAttemptsPoints = 700;
    constexpr int kPenaltyPerAttempt = 35;
    constexpr int kMaxTimePoints = 300;
    constexpr int kPenaltyPerSecond = 3;

    const char* const kCpuName = "CPU";
    const char* const kScoreFile = "scores.txt";
}

// =============================================================================
// 2. Console (única parte dependente de plataforma)
// =============================================================================

namespace console
{
    // Valores iguais aos atributos de cor do console do Windows.
    enum class Color
    {
        Black, DarkBlue, DarkGreen, DarkCyan, DarkRed, DarkMagenta, DarkYellow, Gray,
        DarkGray, Blue, Green, Cyan, Red, Magenta, Yellow, White
    };

    void init()
    {
        #ifdef _WIN32
            SetConsoleOutputCP(CP_UTF8);
            SetConsoleTitleA("Number Hunt");
        #endif
    }

    void setColor(Color color)
    {
        std::cout.flush();
        #ifdef _WIN32
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(color));
        #else
                // Fora do Windows usa ANSI (apenas para facilitar testes).
                const int value = static_cast<int>(color);
                const int ansi = ((value & 1) << 2) | (value & 2) | ((value & 4) >> 2);
                std::cout << "\x1b[" << ((value & 8 ? 90 : 30) + ansi) << "m";
        #endif
    }

    void resetColor()
    {
        setColor(Color::Gray);
    }

    void print(const std::string& text, Color color = Color::Gray)
    {
        setColor(color);
        std::cout << text;
        resetColor();
    }

    void println(const std::string& text = "", Color color = Color::Gray)
    {
        print(text + "\n", color);
    }

    void clear()
    {
        std::cout.flush();
        #ifdef _WIN32
                HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
                CONSOLE_SCREEN_BUFFER_INFO info;
                if (!GetConsoleScreenBufferInfo(handle, &info)) {
                    return;
                }
                const DWORD cells = static_cast<DWORD>(info.dwSize.X) * info.dwSize.Y;
                const COORD origin = {0, 0};
                DWORD written = 0;
                FillConsoleOutputCharacterA(handle, ' ', cells, origin, &written);
                FillConsoleOutputAttribute(handle, info.wAttributes, cells, origin, &written);
                SetConsoleCursorPosition(handle, origin);
        #else
                std::cout << "\x1b[2J\x1b[H";
        #endif
    }

    void sleepMs(int milliseconds)
    {
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }

    void waitKey(const std::string& message = "Pressione qualquer tecla para continuar...")
    {
        print("\n" + message, Color::DarkGray);
        std::cout.flush();
        #ifdef _WIN32
                while (_kbhit()) {
                    _getch();                // descarta teclas pressionadas antes
                }
                const int key = _getch();
                if (key == 0 || key == 224) {
                    _getch();                // teclas especiais enviam dois códigos
                }
        #else
                std::string ignored;
                std::getline(std::cin, ignored);
        #endif
        std::cout << "\n";
    }

    void showHeader(const std::string& title)
    {
        clear();
        println("============================================================", Color::DarkCyan);
        println("  NUMBER HUNT  |  " + title, Color::Cyan);
        println("============================================================\n", Color::DarkCyan);
    }
}

// =============================================================================
// 3. Input (leitura e validação)
// =============================================================================

namespace input
{
    std::string trim(const std::string& text)
    {
        const char* spaces = " \t\r\n";
        const std::size_t first = text.find_first_not_of(spaces);
        if (first == std::string::npos) {
            return "";
        }
        const std::size_t last = text.find_last_not_of(spaces);
        return text.substr(first, last - first + 1);
    }

    std::string readLine(const std::string& prompt)
    {
        console::print(prompt, console::Color::Yellow);
        std::string line;
        if (!std::getline(std::cin, line)) {   // EOF (Ctrl+Z): encerra com elegância
            console::resetColor();
            std::cout << "\n";
            std::exit(0);
        }
        return trim(line);
    }

    std::optional<int> parseInt(const std::string& text)
    {
        int value = 0;
        const char* first = text.data();
        const char* last = first + text.size();
        const std::from_chars_result result = std::from_chars(first, last, value);
        if (result.ec != std::errc() || result.ptr != last) {
            return std::nullopt;
        }
        return value;
    }

    // Repete a pergunta até receber um inteiro dentro de [min, max].
    int readInt(const std::string& prompt, int min, int max)
    {
        while (true) {
            const std::optional<int> value = parseInt(readLine(prompt));
            if (value && *value >= min && *value <= max) {
                return *value;
            }
            console::println("  Entrada inválida. Digite um número inteiro entre " +
                             std::to_string(min) + " e " + std::to_string(max) + ".",
                             console::Color::Red);
        }
    }

    bool readYesNo(const std::string& prompt)
    {
        while (true) {
            std::string answer = readLine(prompt);
            std::transform(answer.begin(), answer.end(), answer.begin(),
                           [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
            if (answer == "s" || answer == "sim") {
                return true;
            }
            if (answer == "n" || answer == "nao" || answer == "não") {
                return false;
            }
            console::println("  Resposta inválida. Digite 's' para sim ou 'n' para não.",
                             console::Color::Red);
        }
    }
}

// =============================================================================
// 4. Random (abstração sobre <random>)
// =============================================================================

class RandomGenerator
{
public:
    RandomGenerator()
    {
        // Mistura random_device com o relógio (random_device é fraco em MinGW antigo).
        std::random_device device;
        const auto now = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        std::seed_seq seed{device(), static_cast<unsigned>(now)};
        engine_.seed(seed);
    }

    // Inteiro pseudo-aleatório com distribuição uniforme em [min, max].
    int nextInt(int min, int max)
    {
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(engine_);
    }

    // Retorna true com a probabilidade informada (0.0 a 1.0).
    bool chance(double probability)
    {
        std::bernoulli_distribution distribution(probability);
        return distribution(engine_);
    }

private:
    std::mt19937 engine_;
};

// =============================================================================
// 5. Pontuação e ranking
// =============================================================================

bool isValidPlayerName(const std::string& name)
{
    if (name.empty() || name.size() > rules::kMaxNameLength) {
        return false;
    }
    // ASCII visível, sem espaços (o arquivo de pontuações usa espaço como separador).
    return std::all_of(name.begin(), name.end(),
                       [](unsigned char c) { return c > 32 && c < 127; });
}

struct GameResult
{
    int attempts = 0;
    double seconds = 0.0;
};

struct ScoreBreakdown
{
    int attemptsPoints = 0;
    int timePoints = 0;

    int total() const
    {
        return attemptsPoints + timePoints;
    }
};

ScoreBreakdown calculateScore(const GameResult& result)
{
    ScoreBreakdown score;
    const int seconds = static_cast<int>(result.seconds);
    score.attemptsPoints = std::max(0, rules::kMaxAttemptsPoints -
                                       rules::kPenaltyPerAttempt * (result.attempts - 1));
    score.timePoints = std::max(0, rules::kMaxTimePoints - rules::kPenaltyPerSecond * seconds);
    return score;
}

struct ScoreEntry
{
    std::string name;
    int score = 0;
};

// Mantém as pontuações ordenadas (maior primeiro) e persiste em arquivo texto.
class ScoreBoard
{
public:
    explicit ScoreBoard(std::string filePath) : filePath_(std::move(filePath)) {}

    void load()
    {
        entries_.clear();
        std::ifstream file(filePath_);
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream stream(line);
            ScoreEntry entry;
            if ((stream >> entry.name >> entry.score) && isValidPlayerName(entry.name) &&
                entry.score >= 0) {
                entries_.push_back(entry);
            }
        }
        sortEntries();
    }

    bool save() const
    {
        std::ofstream file(filePath_, std::ios::trunc);
        for (const ScoreEntry& entry : entries_) {
            file << entry.name << ' ' << entry.score << '\n';
        }
        return static_cast<bool>(file);
    }

    void add(const ScoreEntry& entry)
    {
        entries_.push_back(entry);
        sortEntries();
    }

    std::vector<ScoreEntry> top(std::size_t count) const
    {
        const std::size_t size = std::min(count, entries_.size());
        return std::vector<ScoreEntry>(entries_.begin(), entries_.begin() + size);
    }

private:
    void sortEntries()
    {
        // stable_sort: em empate, quem pontuou primeiro fica na frente.
        std::stable_sort(entries_.begin(), entries_.end(),
                         [](const ScoreEntry& a, const ScoreEntry& b) { return a.score > b.score; });
    }

    std::string filePath_;
    std::vector<ScoreEntry> entries_;
};

// =============================================================================
// 6. Jogadores e partida
// =============================================================================

enum class Hint
{
    TooLow,   // palpite menor que o número secreto
    TooHigh,  // palpite maior que o número secreto
    Correct
};

// Interface comum: a partida não sabe se quem joga é humano ou CPU.
class Player
{
public:
    virtual ~Player() = default;
    virtual int chooseGuess(int attempt) = 0;
    virtual void onHint(int guess, Hint hint) = 0;
};

class HumanPlayer : public Player
{
public:
    int chooseGuess(int attempt) override
    {
        const std::string prompt = "Tentativa " + std::to_string(attempt) + " - Seu palpite (" +
                                   std::to_string(rules::kMinNumber) + "-" +
                                   std::to_string(rules::kMaxNumber) + "): ";
        return input::readInt(prompt, rules::kMinNumber, rules::kMaxNumber);
    }

    void onHint(int, Hint) override {}
};

// Simula um bom jogador humano: faz busca binária "no olho" (palpite perto do meio
// com variação) e, de vez em quando, chuta um valor qualquer dentro do intervalo.
class CpuPlayer : public Player
{
public:
    explicit CpuPlayer(RandomGenerator& random) : random_(random) {}

    int chooseGuess(int attempt) override
    {
        console::print("Tentativa " + std::to_string(attempt) + " - CPU pensando", console::Color::DarkGray);
        console::sleepMs(kThinkTimeMs);
        const int guess = pickGuess();
        console::println(" ... palpite: " + std::to_string(guess), console::Color::White);
        return guess;
    }

    void onHint(int guess, Hint hint) override
    {
        if (hint == Hint::TooLow) {
            low_ = guess + 1;
        } else if (hint == Hint::TooHigh) {
            high_ = guess - 1;
        }
    }

private:
    static constexpr double kSloppyChance = 0.15;  // chance de um palpite descuidado
    static constexpr int kThinkTimeMs = 700;

    int pickGuess()
    {
        if (random_.chance(kSloppyChance)) {
            return random_.nextInt(low_, high_);
        }
        const int middle = low_ + (high_ - low_) / 2;
        const int spread = (high_ - low_) / 8;   // erro de até ~12% do intervalo
        const int jitter = random_.nextInt(-spread, spread);
        return std::clamp(middle + jitter, low_, high_);
    }

    RandomGenerator& random_;
    int low_ = rules::kMinNumber;
    int high_ = rules::kMaxNumber;
};

// Executa uma partida: sorteia o número, pede palpites e mede tentativas e tempo.
class GameSession
{
public:
    explicit GameSession(RandomGenerator& random) : random_(random) {}

    GameResult play(Player& player)
    {
        const int secret = random_.nextInt(rules::kMinNumber, rules::kMaxNumber);
        GameResult result;
        Hint hint = Hint::TooLow;
        const auto start = std::chrono::steady_clock::now();

        do {
            ++result.attempts;
            const int guess = player.chooseGuess(result.attempts);
            hint = compare(guess, secret);
            showHint(hint);
            player.onHint(guess, hint);
        } while (hint != Hint::Correct);

        const std::chrono::duration<double> elapsed = std::chrono::steady_clock::now() - start;
        result.seconds = elapsed.count();
        return result;
    }

private:
    static Hint compare(int guess, int secret)
    {
        if (guess < secret) {
            return Hint::TooLow;
        }
        if (guess > secret) {
            return Hint::TooHigh;
        }
        return Hint::Correct;
    }

    static void showHint(Hint hint)
    {
        switch (hint) {
            case Hint::TooLow:
                console::println("  Muito baixo! O número secreto é MAIOR.\n", console::Color::Cyan);
                break;
            case Hint::TooHigh:
                console::println("  Muito alto! O número secreto é MENOR.\n", console::Color::Yellow);
                break;
            case Hint::Correct:
                console::println("  Acertou!\n", console::Color::Green);
                break;
        }
    }

    RandomGenerator& random_;
};

// =============================================================================
// 7. Aplicação (telas e menu)
// =============================================================================

class Application
{
public:
    Application() : scoreBoard_(rules::kScoreFile) {}

    void run()
    {
        scoreBoard_.load();
        showSplash();

        bool running = true;
        while (running) {
            switch (askMenuChoice()) {
                case MenuOption::PlayHuman:
                    playHumanMatch();
                    break;
                case MenuOption::PlayCpu:
                    playCpuMatch();
                    break;
                case MenuOption::Statistics:
                    showStatistics();
                    break;
                case MenuOption::Quit:
                    running = false;
                    break;
            }
        }
        showGoodbye();
    }

private:
    enum class MenuOption
    {
        PlayHuman = 1,
        PlayCpu,
        Statistics,
        Quit
    };

    // ---- Telas ----------------------------------------------------------------

    void showSplash() const
    {
        static const char* const kLogo[] = {
            R"( _   _  _   _  __  __  ____   _____  ____    _   _  _   _  _   _  _____ )",
            R"(| \ | || | | ||  \/  || __ ) | ____||  _ \  | | | || | | || \ | ||_   _|)",
            R"(|  \| || | | || |\/| ||  _ \ |  _|  | |_) | | |_| || | | ||  \| |  | |  )",
            R"(| |\  || |_| || |  | || |_) || |___ |  _ <  |  _  || |_| || |\  |  | |  )",
            R"(|_| \_| \___/ |_|  |_||____/ |_____||_| \_\ |_| |_| \___/ |_| \_|  |_|  )"};
        static const console::Color kColors[] = {
            console::Color::Red, console::Color::Yellow, console::Color::Green,
            console::Color::Cyan, console::Color::Magenta};

        console::clear();
        console::println("\n");
        for (std::size_t i = 0; i < 5; ++i) {
            console::println(kLogo[i], kColors[i]);
        }
        console::println("\n        Adivinhe o número secreto entre " + std::to_string(rules::kMinNumber) +
                         " e " + std::to_string(rules::kMaxNumber) + "!", console::Color::White);
        console::waitKey();
    }

    MenuOption askMenuChoice() const
    {
        console::showHeader("MENU PRINCIPAL");
        console::println("  [1] Iniciar uma partida", console::Color::Green);
        console::println("  [2] Assistir a CPU jogar sozinha", console::Color::Cyan);
        console::println("  [3] Ver o Top 10 (estatísticas)", console::Color::Yellow);
        console::println("  [4] Sair\n", console::Color::Red);
        return static_cast<MenuOption>(input::readInt("Escolha uma opção (1-4): ", 1, 4));
    }

    void showResult(const std::string& headline, const GameResult& result,
                    const ScoreBreakdown& score) const
    {
        console::println("************************************************************", console::Color::Green);
        console::println("  " + headline, console::Color::Yellow);
        console::println("************************************************************\n", console::Color::Green);

        std::ostringstream seconds;
        seconds << std::fixed << std::setprecision(1) << result.seconds << " s";

        printRow("Tentativas (incluindo a correta)", std::to_string(result.attempts));
        printRow("Tempo", seconds.str());
        printRow("Pontos por tentativas", std::to_string(score.attemptsPoints) + " / " +
                                              std::to_string(rules::kMaxAttemptsPoints));
        printRow("Pontos por tempo", std::to_string(score.timePoints) + " / " +
                                         std::to_string(rules::kMaxTimePoints));
        console::println("\n  PONTUAÇÃO FINAL: " + std::to_string(score.total()), console::Color::Yellow);
    }

    static void printRow(const std::string& label, const std::string& value)
    {
        console::print("  " + label + ": ", console::Color::Gray);
        console::println(value, console::Color::White);
    }

    static std::string formatTableRow(const std::string& position, const std::string& name,
                                      const std::string& score)
    {
        std::ostringstream row;
        row << "  " << std::right << std::setw(3) << position << "   "
            << std::left << std::setw(static_cast<int>(rules::kMaxNameLength)) << name << "   "
            << std::right << std::setw(6) << score;
        return row.str();
    }

    void showStatistics() const
    {
        console::showHeader("TOP 10 - MELHORES PONTUAÇÕES");
        const std::vector<ScoreEntry> entries = scoreBoard_.top(rules::kTopCount);

        if (entries.empty()) {
            console::println("  Nenhuma pontuação registrada ainda. Jogue uma partida!", console::Color::Yellow);
        } else {
            static const console::Color kRankColors[] = {
                console::Color::Yellow, console::Color::White, console::Color::DarkYellow};

            console::println(formatTableRow("POS", "NOME", "PONTOS"), console::Color::Cyan);
            console::println(formatTableRow("---", "------", "------"), console::Color::DarkCyan);
            for (std::size_t i = 0; i < entries.size(); ++i) {
                const console::Color color = i < 3 ? kRankColors[i] : console::Color::Gray;
                console::println(formatTableRow(std::to_string(i + 1), entries[i].name,
                                                std::to_string(entries[i].score)), color);
            }
        }
        console::waitKey();
    }

    void showGoodbye() const
    {
        console::showHeader("ATÉ LOGO");
        console::println("  Obrigado por jogar Number Hunt!\n", console::Color::Green);
    }

    // ---- Partidas -------------------------------------------------------------

    std::string askPlayerName() const
    {
        while (true) {
            const std::string name = input::readLine("Digite seu nome (1 a " +
                                                     std::to_string(rules::kMaxNameLength) +
                                                     " caracteres ASCII, sem espaços): ");
            if (isValidPlayerName(name)) {
                return name;
            }
            console::println("  Nome inválido. Use de 1 a " + std::to_string(rules::kMaxNameLength) +
                             " caracteres ASCII visíveis, sem espaços.", console::Color::Red);
        }
    }

    // Joga uma rodada com qualquer tipo de jogador, mostra o resultado e salva a pontuação.
    void playRound(Player& player, const std::string& name, const std::string& headline)
    {
        GameSession session(random_);
        const GameResult result = session.play(player);
        const ScoreBreakdown score = calculateScore(result);

        showResult(headline, result, score);

        scoreBoard_.add({name, score.total()});
        if (!scoreBoard_.save()) {
            console::println("\n  Aviso: não foi possível salvar a pontuação em arquivo.", console::Color::Red);
        }
    }

    void playHumanMatch()
    {
        console::showHeader("NOVA PARTIDA");
        const std::string name = askPlayerName();

        bool playAgain = true;
        while (playAgain) {
            console::showHeader("JOGADOR: " + name);
            console::println("  Pensei em um número entre " + std::to_string(rules::kMinNumber) + " e " +
                             std::to_string(rules::kMaxNumber) + ". Consegue adivinhar?\n",
                             console::Color::White);

            HumanPlayer player;
            playRound(player, name, "PARABÉNS, " + name + "! VOCÊ ACERTOU!");
            playAgain = input::readYesNo("\nDeseja jogar de novo? (s/n): ");
        }
    }

    void playCpuMatch()
    {
        console::showHeader("A CPU VAI JOGAR SOZINHA");
        console::println("  Pensei em um número entre " + std::to_string(rules::kMinNumber) + " e " +
                         std::to_string(rules::kMaxNumber) + ". Vamos ver se a CPU acerta!\n",
                         console::Color::White);

        CpuPlayer cpu(random_);
        playRound(cpu, rules::kCpuName, "A CPU ACERTOU O NÚMERO!");
        console::waitKey();
    }

    RandomGenerator random_;
    ScoreBoard scoreBoard_;
};

// =============================================================================
// main
// =============================================================================

int main()
{
    console::init();
    Application app;
    app.run();
    return 0;
}

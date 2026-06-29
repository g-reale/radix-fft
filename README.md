<p align="center">
  <strong>radix-fft — Real-Time Audio Visualizer</strong>
</p>

This repository contains the implementation of a **real-time audio visualizer** developed in C++. The system captures the system's audio signal using the PulseAudio simplified API (loopback), computes the Fast Fourier Transform (FFT) using a manually implemented Radix-2 DIT (Decimation in Time) algorithm, and uses the ncurses library for terminal color control and dynamic visual display based on the energy of low (bass) and high (treble) frequencies.

## Objective

- Manually implement the Radix-2 Fast Fourier Transform (FFT) algorithm in C++.
- Capture and process real-time audio streams via PulseAudio.
- Apply post-processing techniques such as Exponentially Weighted Moving Average (EWMA) and normalization for signal smoothing.
- Create a dynamic terminal-based interface (ncurses) that changes colors and visual elements in response to the audio.

## Technologies Used

- **Language:** C++ (C++11 standard)
- **Audio APIs:** PulseAudio (libpulse, libpulse-simple)
- **Terminal Interface:** ncurses
- **Graphical Interface/Others:** X11, libjpeg (dependencies in Makefile)
- **Threads:** pthread
- **Build System:** GNU Make
- **Platform:** Linux

## Project Structure

```bash
radix-fft/
├── src/
│   ├── main.cpp           # Main application loop and ncurses control
│   ├── Fft.cpp            # Radix-2 DIT FFT algorithm implementation
│   ├── Sound.cpp          # PulseAudio audio capture
│   ├── PlotSlider.cpp     # Visual elements (widgets)
│   ├── Slider.cpp         # Slider controls for the interface
│   ├── PostProcessor.cpp  # Smoothing filters (EWMA, normalization, energy)
│   └── Comunication.cpp   # Communication with external drivers
├── include/               # Corresponding header files (.hpp)
├── scripts/
│   ├── init_loopback.sh   # Loads the PulseAudio loopback module
│   ├── stop_loopback.sh   # Unloads the PulseAudio loopback module
│   └── run.sh             # Configures the environment and runs the visualizer
├── resources/             # Assets, gradient images
└── Makefile               # Project compilation rules
```

## How to Run the Project

```bash
git clone https://github.com/g-reale/radix-fft.git
cd radix-fft
```

### Setting Up Audio Loopback

To allow the program to capture the system's output audio (what is playing on the computer), the PulseAudio loopback device must be enabled:

```bash
./scripts/init_loopback.sh
```

### Compiling and Running

```bash
# Compile the executable
make

# Run the visualizer
./scripts/run.sh
```

### Exiting

To close the application, interrupt the process in the terminal (`Ctrl+C`) and disable loopback:

```bash
./scripts/stop_loopback.sh
```

## Environment Setup

- **g++ compiler** with C++11 support
- **PulseAudio** installed and running
- **ncurses** development library
- **X11** and **libjpeg** libraries

```bash
# Installation of dependencies (Ubuntu/Debian)
sudo apt-get install build-essential libasound2-dev libpulse-dev libncurses5-dev libncursesw5-dev libx11-dev libjpeg-dev
```

## Workflow

1. The `init_loopback.sh` script redirects the system's audio output to a capture source.
2. The `Sound` class initializes the connection with PulseAudio and continuously listens to the audio buffers.
3. At each iteration, the collected audio samples are passed to the `Fft` class.
4. The **Radix-2 DIT FFT** algorithm computes frequency coefficients from the time-domain signal.
5. The `PostProcessor` class calculates energy in the bass and treble ranges, applying normalization and EWMA filters to smooth transitions.
6. The main program updates terminal colors and displays via `ncurses`, mapping bass and treble levels to a dynamic palette (based on the gradient image in `resources/`).

## Notes

- Execution depends on the correct functioning of the PulseAudio sound server. On systems running pure PipeWire without PulseAudio compatibility, additional emulation settings may be required.
- The source code mentions communication improvements with Arduino hardware and the creation of a dynamic graphical interface in the notes within `plans.md`.

---

<p align="center">
  <strong>radix-fft — Visualizador de Áudio em Tempo Real</strong>
</p>

Este repositório contém a implementação de um **visualizador de áudio em tempo real** desenvolvido em C++. O sistema realiza a captura de sinal de áudio do sistema utilizando a API simplificada do PulseAudio (loopback), computa a Transformada Rápida de Fourier (FFT) usando um algoritmo Radix-2 DIT (Decimação no Tempo) implementado manualmente, e utiliza a biblioteca ncurses para controle de cores do terminal e exibição visual dinâmica baseada na energia das frequências baixas (graves) e altas (agudos).

## Objetivo

- Implementar o algoritmo de Transformada Rápida de Fourier (FFT) Radix-2 de forma manual em C++.
- Capturar e processar fluxo de áudio em tempo real via PulseAudio.
- Aplicar técnicas de pós-processamento como Média Móvel Exponencialmente Ponderada (EWMA) e normalização para suavização do sinal.
- Criar uma interface dinâmica baseada em terminal (ncurses) que altera cores e elementos visuais em resposta ao áudio.

## Tecnologias Utilizadas

- **Linguagem:** C++ (padrão C++11)
- **APIs de Áudio:** PulseAudio (libpulse, libpulse-simple)
- **Interface de Terminal:** ncurses
- **Interface Gráfica/Outros:** X11, libjpeg (dependências no Makefile)
- **Threads:** pthread
- **Build System:** GNU Make
- **Plataforma:** Linux

## Estrutura do Projeto

```bash
radix-fft/
├── src/
│   ├── main.cpp           # Loop principal da aplicação e controle do ncurses
│   ├── Fft.cpp            # Implementação do algoritmo Radix-2 DIT FFT
│   ├── Sound.cpp          # Captura de áudio do PulseAudio
│   ├── PlotSlider.cpp     # Elementos visuais (widgets)
│   ├── Slider.cpp         # Controle de sliders para interface
│   ├── PostProcessor.cpp  # Filtros de suavização (EWMA, normalização, energia)
│   └── Comunication.cpp   # Comunicação com drivers externos
├── include/               # Arquivos de cabeçalho (.hpp) correspondentes
├── scripts/
│   ├── init_loopback.sh   # Carrega o módulo de loopback do PulseAudio
│   ├── stop_loopback.sh   # Descarrega o módulo de loopback do PulseAudio
│   └── run.sh             # Configura o ambiente e executa o visualizador
├── resources/             # Assets, imagens de gradientes
└── Makefile               # Regras de compilação do projeto
```

## Como Executar o Projeto

```bash
git clone https://github.com/g-reale/radix-fft.git
cd radix-fft
```

### Configurando o Loopback de Áudio

Para que o programa capture o áudio de saída do sistema (o que está tocando no computador), é necessário ativar o dispositivo de loopback do PulseAudio:

```bash
./scripts/init_loopback.sh
```

### Compilando e Executando

```bash
# Compilar o executável
make

# Executar o visualizador
./scripts/run.sh
```

### Encerrando

Para finalizar a aplicação, interrompa o processo no terminal (`Ctrl+C`) e desative o loopback:

```bash
./scripts/stop_loopback.sh
```

## Configuração do Ambiente

- **Compilador g++** com suporte a C++11
- **PulseAudio** instalado e rodando
- Biblioteca de desenvolvimento **ncurses**
- Bibliotecas **X11** e **libjpeg**

```bash
# Instalação das dependências (Ubuntu/Debian)
sudo apt-get install build-essential libasound2-dev libpulse-dev libncurses5-dev libncursesw5-dev libx11-dev libjpeg-dev
```

## Fluxo de Funcionamento

1. O script `init_loopback.sh` redireciona a saída de áudio do sistema para uma fonte de captura.
2. A classe `Sound` inicializa a conexão com o PulseAudio e escuta continuamente os buffers de áudio.
3. A cada iteração, as amostras de áudio coletadas são passadas para a classe `Fft`.
4. O algoritmo **Radix-2 DIT FFT** calcula os coeficientes de frequência a partir do sinal temporal.
5. A classe `PostProcessor` calcula a energia nas faixas de graves e agudos, aplicando normalização e filtros EWMA para suavizar transições.
6. O programa principal atualiza as cores e o display do terminal via `ncurses` mapeando os níveis de graves e agudos em uma paleta dinâmica (baseada na imagem de gradiente em `resources/`).

## Observações

- A execução depende do correto funcionamento do servidor de som PulseAudio. Em sistemas que utilizam PipeWire pura sem compatibilidade PulseAudio, pode requerer configurações adicionais de emulação.
- O código-fonte faz menção a melhorias de comunicação com hardware Arduino e criação de uma interface gráfica dinâmica nas notas de `plans.md`.

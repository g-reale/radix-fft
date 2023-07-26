# Arquitetura

TODO:

- determinar os tipos e algoritimo de casting entre Fft e Sound
- comunicação com o hardware
- calcular os requisitos para atualização com frequência de 60hz

## Fft

## Sound

Tornar o programa de sound uma classe com as seguintes responsabilidades:

- durante a inicialização:
    - ler um arquivo com as configurações da sink
        - tamanho do buffer
        - frequência de amostragem
        - fonte
        - ...
    - inicializar a sink
- fornecer uma função para a leitura de amostras
- apagar a sink no destrutor

mock class header
```
    class Sound{
        private:
            int buff_size;
            int buff_exp;
            pa_simple * stream;
        
        public:
            vector<> samples;
            
            Sound(string path);
            ~Sound();
            int getBuffSize();
            int getBuffExp();
    }
```

mock config file
```
something something...
```

## Driver | Comunication

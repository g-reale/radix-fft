# Arquitetura

TODO:

- determinar o tipo das amostras de audio
- comunicação com o hardware
- calcular os requisitos para atualização com frequência de 60hz

## Fft

Receber como entrada o tipo `const uint8_t *` ao envéz de `vetor<complex<uint_8>>`:

O novo tipo de samples é organizado de forma diferente: um frame (conjunto de uma amostra esquerda e uma direita(stereo)) inicia no índice `2*i`(esquerda) e termina em `2*i+1`(direita)

Cada frame será transformado em um valor complexo, com a amostra da esquerda sendo real e a da direita imaginária

A etapa de ordenação da amostra será utilizada para implementar essa conversão, i.e. o frame será ordenado e "castado" ao mesmo tempo

**Lembra que:** como o índice do frame envolve uma multiplicação por 2, no método que dertermina os índices das amostras, converti para o índice do frame (i<<1) multiplicando o índice da amostra por 2


## Sound

Tornar o programa de sound uma classe com as seguintes responsabilidades:

- durante a inicialização:
  - conectar com a sink
  - alocar um vetor de amostras
- fornecer uma função para a leitura de amostras
- durante a destrução:
  - apagar o vetor de amostras
  - desconectar da sink

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

## Driver | Comunication

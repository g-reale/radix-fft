# Arquitetura

TODO:

- comunicação com o hardware
- calcular os requisitos para atualização com frequência de 60hz
- dimensões dinamicas da gui e testes de parâmetros para os widgets

## Coloring

reorganizar o PostProcessor como uma composição de classes
    lowPassFilter
    highPassFilter
    adpatativaNormalizer
    smootheningFilter (https://en.wikipedia.org/wiki/Exponential_smoothing)

o par ordenado em alguma funcação g(x,y): [0 - 1]² -> [0 - 255]³ (vou usar uma imagem)

## Driver | Comunication

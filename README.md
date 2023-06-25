# charge-point-pmr3402
Esse é o repositório que contém o código para o trabalho de Sistemas Embarcados - PMR3402.

# Instruções para rodar o código
## Parte do ESP32
Abra o VSCode, instale a extensão PlatformIO e abra esse repositório como um projeto

## Parte do servidor
O servidor foi feito utilizando o seguinte projeto Open Source: 

https://github.com/steve-community/steve

Para rodar basta seguir as instruções especificas ao seu sistema operacional e depois seguir essas instruções:
```bash
cd ~/steve-steve-3.6.0
java -jar target/steve.jar
lt --port 8080 --subdomain pmr3402
```
# NodeHealthGuard
Node HealthGuard: Um Sistema de Alerta Precoce para Emergências Médicas 

Este projeto apresenta o desenvolvimento de um sistema de alerta precoce para emergências médicas
utilizando NodeMCU ESP8266. O sistema monitora a frequência cardíaca em tempo real. Quando Alguns dos
parâmetros excede limites pré-determinados, um alerta é acionado, indicando uma possível emergência médica. 
Este projeto tem como objetivo contribuir para a promoção de uma vida saudável e bem-estar para todos, em 
conformidade com o Objetivo de Desenvolvimento Sustentável 3.


Nos últimos anos, houve um aumento significativo no desenvolvimento de tecnologias voltadas para a saúde, 
visando melhorar o monitoramento e prevenção de doenças. Um dos desafios enfrentados é a detecção precoce de
situações médicas emergenciais, como paradas cardíacas. Nesse contexto, este projeto propõe a criação de um 
sistema de alerta precoce que utiliza sensores conectados a um microcontrolador NodeMCU ESP8266 para monitorar
constantemente os sinais vitais de uma pessoa.
A ideia de utilizar dispositivos eletrônicos para monitorar a saúde não é nova. Nos últimos anos, várias 
pesquisase projetos foram desenvolvidos para criar sistemas semelhantes. No entanto, muitos desses sistemas são
complexos e caros, limitando sua acessibilidade. Este projeto busca oferecer uma solução simples e acessível, 
utilizando componentes eletrônicos de baixo custo e programação.
A relevância deste projeto está alinhada com o Objetivo de Desenvolvimento Sustentável 3 das Nações Unidas, 
que visa assegurar uma vida saudável e promover o bem-estar para todos, em todas as idades. Ao criar um 
sistema de alerta precoce para emergências médicas, este projeto contribui para a redução da mortalidade 
prematura e para o acesso universal aos serviços de saúde.

#Componentes utilixados:

1 - NodeMCU ESP8266
2 - Módulo AD8232 
3 - Módulo Display LCD 16x2 com comunicação I2C
4 - Jumpers
5 - breadboard

Software utilizado:

1 - Arduino IDE
2 - Servidor MQTT ubidots

=========================== Funcionamento =================================

O protótipo consiste em um sistema que monitora o ritmo cardíaco de uma pessoa usando um sensor ECG 
(eletrocardiograma) e exibe as leituras em um LCD. Além disso, o sistema se conecta a uma rede Wi-Fi 
e envia os dados do ritmo cardíaco para um servidor MQTT (Message Queuing Telemetry Transport) hospedado
na nuvem, permitindo a monitoração remota em tempo real.

#Sensores e Atuadores:

1.	Sensor ECG: O sensor ECG é conectado ao microcontrolador ESP8266 (NodeMCU) através de uma entrada analógica.
   Ele mede a atividade elétrica do coração e gera sinais proporcionais aos batimentos cardíacos.

2.	LCD 16x2 I2C: O LCD é usado para exibir informações importantes, como o status da conexão Wi-Fi e o ritmo cardíaco.
    Ele é conectado ao microcontrolador através da comunicação I2C, o que simplifica a interface e economiza pinos.

3.	Conexão Wi-Fi: O microcontrolador se conecta a uma rede Wi-Fi usando as credenciais configuradas no código.
   Isso permite que o dispositivo se comunique com o servidor MQTT e envie os dados do ritmo cardíaco pela internet.

#Sequência de funcionamento:

1.	Inicialização: O sistema é inicializado e configurações iniciais são realizadas, incluindo a conexão Wi-Fi, a
   configuração do servidor MQTT e a inicialização do LCD.

2.	Monitoramento do Ritmo Cardíaco: O sensor ECG é lido periodicamente pelo microcontrolador. A leitura é convertida
    em batimentos cardíacos por minuto (BPM), um formato adequado para exibição.

3.	Exibição no LCD: As leituras do ritmo cardíaco são exibidas no LCD. Além disso, o status da conexão Wi-Fi pode ser
    exibido uma vez quando conectado, conforme solicitado.

4.	Envio de Dados MQTT: Os dados do ritmo cardíaco são enviados periodicamente para o servidor MQTT através da conexão
    Wi-Fi. O servidor MQTT atua como um intermediário para distribuir esses dados a qualquer dispositivo que esteja inscrito
     nos tópicos relevantes.

5.	Monitoramento Remoto: Os dados do ritmo cardíaco podem ser monitorados remotamente em tempo real por meio de qualquer
    dispositivo que esteja inscrito nos tópicos MQTT relevantes, como um aplicativo móvel ou um painel de controle web.

#Integração com MQTT Broker:

O microcontrolador utiliza a biblioteca PubSubClient para estabelecer uma conexão com o servidor MQTT, configurado com o endereço 
do broker MQTT e a porta padrão. Ele publica os dados do ritmo cardíaco em um tópico específico no servidor MQTT, permitindo que 
qualquer cliente MQTT inscrito neste tópico receba e processe os dados conforme necessário.
Em resumo, o sistema integra sensores para coletar dados do ritmo cardíaco, atuadores para exibir informações localmente e se comunica 
com um servidor MQTT para enviar os dados coletados, permitindo monitoramento remoto e processamento adicional.

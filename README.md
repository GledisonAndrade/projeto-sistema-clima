Projeto **** Sistema  Clima ****

Este sistema é voltado para pequenos agricultores para monitorar situação climática de sua região, lembrando este é prototípico mas sempre levando em consideração a evolução.



Estação Meteorológica IoT OFFLINE com registro histórico em SD.



Criação do negócio : A maioria das soluções IoT depende de:

Internet
Wi-Fi rural
Mensalidades
Infraestrutura de rede
Pequenos agricultores não possuem internet constante no campo.

Isso torna soluções conectadas inviáveis.



Solução proposta: 

1: Funcionamento 100% offline

2: Registro automático em cartão SD

  3: Histórico climático confiável

  4: Baixíssimo custo

  5: Sem mensalidade

6: O agricultor apenas remove o cartão SD e abre o relatório no computador ou celular.



Proposta: Estação meteorológica que funciona sem internet e gera relatórios automáticos do clima para apoio à decisão agricultura familiar e pequenos agricultores.

Benefícios  direto a esse publico: 

Saber meses mais secos ou chuvosos
Identificar épocas de frio intenso
Planejar irrigação
Planejar plantio e colheita
Reduzir desperdício de água


Valor financeiro desse projeto: 

 

item                                         valor estimado



custo de produção :                 180~250







valor de venda:                          $ 350~450



Receitas futuras:



Venda do kit
Atualizações de firmware
Versão PRO com internet (upgrade)
Modelo escalável por evolução tecnológica.





Ecossistema ITU-T:   ITU-T define IoT como dispositivos que coletam e processam dados.  

    

   Camada ITU-T

 Aplicação real

   Dispositivos

 Sensores + Arduino

   Gateway local

 Arduino processa dados

   Armazenamento

 Cartão SD

   Aplicação

 Usuário analisa relatório

   

Observação : Neste caso é chamado de IoT Local / Edge IoT ou processamento na borda (Edge Computing)   

  

Documentação do projeto:



Descrição da aplicação



A aplicação consiste em uma estação meteorológica de baixo custo que:

Coleta dados climáticos continuamente
Armazena em cartão SD
Permite consulta de histórico
Permite reset completo do sistema
Pode receber atualizações via USB
O sistema auxilia agricultores na tomada de decisões baseada em histórico climático real da propriedade.





Modelo de domínio   (UML- Descrição)



Atores:

1:Agricultor

2:Estação meteorológica

3:Computador (leitura do SD)

4:Técnico (atualização via USB)



   Entidade

 Descrição

   Sensores

 Capturam dados ambientais

   Estação

 Processa dados

   Cartão SD

 Armazena histórico

   Usuário

 Analisa relatórios

   Firmware

 Pode ser atualizado

   

Relações  UML (descrição textual):



Sensores → enviam dados → Estação

Estação → grava dados → Cartão SD

Usuário → lê dados → Computador

Técnico → atualiza → Firmware via USB.





Modelo informacional:  Dados registrado no arquivo txt

Exemplo real do relatório:





TEMPERATURA T: 28°C

UMIDADE U: 55%
LUMINOSIDADE: DIA( simbologia) NOITE(simbologia)
CLIMA: TEMPO BOM + (simbologia)
 


Tipos de dados armazenados:



   Campo

 Tipo

   

 

   

 

   Temperatura

 Numérico

   Umidade

 Numérico

   Luminosidade

 Simbologia  

   Classificação clima

 Texto e Simbologia.

   

Modelo Funcional (UML-Casos de uso)

Casos de uso principais:

Coletar dados automaticamente

Sistema mede clima continuamente
Gravar no cartão SD

Dados salvos em arquivo TXT
Consultar histórico

Botão permite visualizar últimos registros
Resetar sistema

Botão limpa dados do SD
Sistema volta ao padrão inicial
Atualizar firmware

Via USB usando Arduino IDE


Modelo de comunicação: 



Como o sistema é offline:

Comunicação interna



   Origem

 Destino

 Meio

   Sensor → Arduino

 Pinos digitais

 

   Arduino → SD

 Interface SPI

 

   Botões → Arduino

 Pinos digitais

 

   USB → Arduino

 Serial

 

   

Comunicação totalmente local (Edge IoT).







Implantação da arquitetura desse projeto:

Arquitetura embarcada offline:

Sensores → Arduino → Tela→  Cartão SD → Usuário



Hardware do Projeto

   Componente

 Função

   Arduino Uno

 Microcontrolador

   Sensor DHT

 Temperatura/umidade

   LDR

 Dia/noite

   Módulo SD

 Armazenamento

   Botão Histórico

 Consulta dados

   Botão Reset

 Limpar memória

   LEDs

TELA LCD16x2

 Alertas visuais

Imprime dados na tela

   

Atualizações do sistema:  Este projeto é acompanhado de melhoria com novas implementações a ser geradas, com objetivo de evolução e  desempenho melhor do projeto e software.

O sistema permite:

* Atualização de firmware via USB

*Melhoria contínua do produto

*Possível evolução futura para versão online

tendo assim uma escalabilidade tecnológica,



Conclusão projeto:

O projeto apresenta uma solução IoT:

Acessível
Offline
Escalável
Realista para o campo brasileiro
A coleta histórica de dados climáticos permite decisões agrícolas mais assertivas, reduzindo riscos e aumentando produtividade.





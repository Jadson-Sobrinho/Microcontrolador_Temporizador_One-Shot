# Documentação do Código - Controle de LEDs com Botão no Raspberry Pi Pico

## Visão Geral
Este programa controla três LEDs conectados ao Raspberry Pi Pico, acionados por um botão. Quando o botão é pressionado, os LEDs acendem em sequência e são desligados após um tempo pré-definido. Durante essa sequência, o botão não pode ser pressionado novamente até que o último LED seja apagado.

## Dependências
- **Biblioteca Padrão do C**: `stdio.h`.
- **Biblioteca Padrão do Raspberry Pi Pico**: `pico/stdlib.h` para controle de GPIO, temporização e comunicação serial.
- **Biblioteca de Temporização**: `pico/time.h` para gerenciar delays e alarmes.

## Hardware Utilizado
- **Raspberry Pi Pico**
- **LEDs:** Conectados aos pinos GPIO 11 (Verde), GPIO 12 (Azul) e GPIO 13 (Vermelho).
- **Botão:** Conectado ao GPIO 5 com pull-up interno habilitado.

## Funcionamento
1. O botão é pressionado.
2. Após um pequeno delay para debounce, os LEDs são acesos.
3. Cada LED apaga após um tempo programado:
   - Verde: 3 segundos
   - Azul: 6 segundos
   - Vermelho: 9 segundos
4. Apenas após o LED vermelho apagar, o botão pode ser pressionado novamente.

## Variáveis Globais
- `bool led_sequence_active`: Controla se uma sequência de LEDs está em andamento.

## Funções
### `int64_t turn_off_callback_red(alarm_id_t id, void *user_data)`
Desliga o LED vermelho e libera o botão para nova ativação.

### `int64_t turn_off_callback_green(alarm_id_t id, void *user_data)`
Desliga o LED verde.

### `int64_t turn_off_callback_blue(alarm_id_t id, void *user_data)`
Desliga o LED azul.

### `int main()`
- Inicializa GPIOs.
- Configura o botão com pull-up interno.
- Verifica o estado do botão e inicia a sequência de LEDs caso nenhum esteja ativo.

## Fluxo do Programa
1. Aguarda o pressionamento do botão.
2. Se a sequência de LEDs não estiver em andamento:
   - Acende os LEDs e inicia os temporizadores.
   - Os LEDs apagam após os tempos definidos.
   - O botão só pode ser pressionado novamente após o LED vermelho apagar.
3. Loop infinito com pequena pausa para evitar uso excessivo da CPU.

## Melhorias Possíveis
- Implementar um sistema de interrupção para capturar o pressionamento do botão.
- Alterar a sequência de iluminação de acordo com padrões pré-definidos.
- Adicionar um feedback sonoro ao pressionar o botão.

## Conclusão
Este programa demonstra o uso de GPIOs e temporização no Raspberry Pi Pico para controlar LEDs em resposta ao acionamento de um botão. A lógica impede que o botão seja pressionado novamente antes do fim da sequência, garantindo um funcionamento previsível e organizado.


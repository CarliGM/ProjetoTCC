// Botões
const int BOTAO_UP = 2;
const int BOTAO_DOWN = 3;
const int BOTAO_OK = 4;

// Estado do sistema
enum Estado {
  MENU,
  OPCAO1,
  OPCAO2,
  OPCAO3
};

Estado estadoAtual = MENU;
int opcaoSelecionada = 0;
const int totalOpcoes = 3;

void setup() {
  Serial.begin(9600);

  pinMode(BOTAO_UP, INPUT_PULLUP);
  pinMode(BOTAO_DOWN, INPUT_PULLUP);
  pinMode(BOTAO_OK, INPUT_PULLUP);
}

void loop() {
  lerBotoes(); // Atualiza estado ou seleção
  executarEstado(); // Executa a lógica do estado atual
  delay(10); // Pequeno delay para estabilidade
}

void lerBotoes() {
  static unsigned long ultimoDebounce = 0;
  if (millis() - ultimoDebounce < 200) return; // debounce simples

  if (botaoPressionado(BOTAO_UP)) {
    if (estadoAtual == MENU) {
      opcaoSelecionada = (opcaoSelecionada - 1 + totalOpcoes) % totalOpcoes;
      Serial.print("Selecionado: ");
      Serial.println(opcaoSelecionada + 1);
    }
    ultimoDebounce = millis();
  }

  if (botaoPressionado(BOTAO_DOWN)) {
    if (estadoAtual == MENU) {
      opcaoSelecionada = (opcaoSelecionada + 1) % totalOpcoes;
      Serial.print("Selecionado: ");
      Serial.println(opcaoSelecionada + 1);
    }
    ultimoDebounce = millis();
  }

  if (botaoPressionado(BOTAO_OK)) {
    if (estadoAtual == MENU) {
      if (opcaoSelecionada == 0) estadoAtual = OPCAO1;
      else if (opcaoSelecionada == 1) estadoAtual = OPCAO2;
      else if (opcaoSelecionada == 2) estadoAtual = OPCAO3;
    } else {
      estadoAtual = MENU; // Volta ao menu ao pressionar OK fora do menu
    }
    ultimoDebounce = millis();
  }
}

void executarEstado() {
  if (estadoAtual == MENU) {
    exibirMenu();
  } else if (estadoAtual == OPCAO1) {
    executarOpcao1();
  } else if (estadoAtual == OPCAO2) {
    executarOpcao2();
  } else if (estadoAtual == OPCAO3) {
    executarOpcao3();
  }
}

void exibirMenu() {
  Serial.print("Menu - Opção ");
  Serial.println(opcaoSelecionada + 1);
}

void executarOpcao1() {
  Serial.println("Executando OPÇÃO 1");
}

void executarOpcao2() {
  Serial.println("Executando OPÇÃO 2");
}

void executarOpcao3() {
  Serial.println("Executando OPÇÃO 3");
}

bool botaoPressionado(int pino) {
  return digitalRead(pino) == LOW;
}

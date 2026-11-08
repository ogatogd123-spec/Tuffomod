# Tuffo Mod — projeto Geode

Projeto inicial de um mod para Geometry Dash **2.2091**, pensado para Geode Mobile.

## O que já está no projeto
- Botão **TUFFO** no menu principal.
- Janela própria do Tuffo Mod.
- Três opções booleanas configuráveis pelo painel de configurações do Geode:
  - Mostrar botão do Tuffo
  - Interface personalizada
  - Opções rápidas

## Importante
Este ZIP contém o **código-fonte do projeto**, não um `.geode` pronto nem um APK.
Para gerar o mod instalável, é necessário compilar com o Geode SDK correspondente à versão/plataforma.

## Estrutura
- `mod.json` — identificação, versões-alvo e configurações.
- `CMakeLists.txt` — configuração de compilação.
- `src/main.cpp` — botão e janela do mod.

## Compilação
1. Instale/configure o Geode SDK compatível com Geometry Dash 2.2091 e Android arm64.
2. Defina `GEODE_SDK` apontando para a pasta do SDK.
3. Configure e compile o projeto com CMake conforme as instruções da versão do Geode SDK instalada.
4. Instale o arquivo `.geode` gerado pelo Geode.

## Observação de compatibilidade
O número de versão do Geode SDK e algumas APIs podem variar entre builds. Este projeto é um ponto de partida e pode precisar de pequenos ajustes após compilar com o SDK exato usado no seu Geode Mobile.

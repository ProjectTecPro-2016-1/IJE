### Telas

#### Attract mode

Um modo de atrair a atenção do jogador, e motivá-lo a iniciar uma partida, é
exibir material do jogo automaticamente caso a tela de apresentação do jogo
fique parada por muito tempo. A implementação desta exibição é denominada
_attract mode_.

O attract mode pode ser um estágio do jogo sendo jogado automaticamente, pode
conter imagens com a história do jogo, etc. É importante definir, no GDD,
quanto tempo levará para que o attract mode entre em ação a partir da tela de
apresentação, sua duração e forma.

#### Tela de abertura

A tela de abertura do jogo é deveras importante, no sentido de que é o
primeiro contato do jogador com o jogo. Devem ser detalhados, no GDD:

1. qual a imagem a ser exibida;
2. como a imagem será exibida;
3. a descrição de quaisquer animações que possam fazer parte desta
tela de abertura;
4. a lista das opções que o jogador terá (modos de jogo, tela de
opções e/ou configurações, carregar jogo, créditos, etc);
5. modo de interface com esta tela (teclado, mouse, ambos, etc);
6. descrição do modo de salvar e/ou carregar um arquivo de progresso;
7. modo de interface para se  determinar o nome do arquivo de
progresso (teclado virtual ou físico, automático, etc);
8. detalhes do arquivo de progresso a serem exibidos (nome, data,
nível, tempo de jogo, imagem ilustrativa, etc);
9. Opções a disposição do jogador (gráficos, música, efeitos sonoros,
dificuldade, legendas, idioma, contraste, controles, etc). Estas opções
comporão, se necessário, a tela de opções (caso sejam poucas, estas
opções podem fazer parte da própria tela de abertura).

#### Outras telas

Outras telas que fazem parte do jogo, e que também devem ser detalhadas,
são a tela de créditos (com o nome/imagem dos membros da equipe e
colaboradores), material extra (galeria de arte, conquistas, colecionáveis e
desbloqueáveis, vídeos, etc).

Importante detalhar, para cada tela extra, o conteúdo que fará parte dela e
como será a interface do jogador com este conteúdo. Além disso, é importante
fazer um gráfico como o fluxo destas telas, a partir da tela inicial, apontando
como chegar a uma delas a partir das outras (um grafo direcionado das telas
que compõem o jogo).

#### Tela de carregamento

Outra tela importante, que surge ao longo do jogo, é a tela de carregamento
(_loading screen_). Caso o jogo tenha momentos de carregamento que
não sejam imediatos, é importante compôr uma tela de carregamento que dê ao
jogador um feedback visual deste carregamento, e o quanto falta para ele ser
finalizado.

Devem ser descrito, em detalhes,

1. quais imagens serão apresentadas nesta tela;
2. quais informações a respeito do carregamento serão apresentadas ao
jogador (barra de progresso, porcentagem, animação, etc);
3. outras informações, como dicas, perguntas sobre o jogo, minigame, etc.

### Outputs

Um capítulo ou seção do GDD, descrevendo as telas listadas acima.

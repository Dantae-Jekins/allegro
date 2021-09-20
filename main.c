#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
//#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define height 720
#define width 1080

// Estruturas do jogo
#define caixas 8 
struct caixa
{
	bool existe; //caixa existe?
	bool texto;  //possui texto?
	
	// variáveis para a caixa
	int pos[2];
	int siz[2];
	int type;

	// variáveis para o texto
	char *text;
	ALLEGRO_FONT *font;
} box[caixas];


bool setup(void)
{
	// Retorna true se concluído com sucesso
	// ou false se ocorreu algum erro.
	
	// Inicializa as estruturas
	for (size_t i = 0; i < caixas; i++)
	{
		box[i].existe = false;
		box[i].texto = false;
	}

	// Inicializa o ALLEGRO
	bool checkup = true;
	if (!al_init())
	{
		printf("\nal_init não inicializado");
		checkup = false;
	}
	if (!al_install_keyboard())
	{
		printf("\nal_install_keyboard não inicializado");
		checkup = false;
	}
	if (!al_init_font_addon())
	{
		printf("\nal_init_font_addon não inicializado");
		checkup = false;
	}
	if (!al_init_ttf_addon())
	{
		printf("\nal_init_ttf_addon não inicializado");
		checkup = false;
	}

	return checkup;
	// permite que a função analise vários de
	// uma vez, sem parar no primeiro.
}


int genBox()
{
	// prepara uma estrutura "box" de posições, tamanhos definidos
	// e que deve ser renderizada por outra função.
	int ID = -1;
	printf("\nBUSCANDO BLOCO LIVRE");
	for (size_t i = 0; i < caixas; i++)
	{
		// loop entre os blocos para ver qual está dispodinível
		if (!box[i].existe)
		{
			// achou um bloco disponível
			ID = i;
			box[ID].existe = true;
			printf("\nBLOCO LIVRE ID.%d",ID);
			break;
		}
	}
	if (ID < 0)
	{
		printf("\nNÃO EXISTEM BLOCOS DISPONÍVEIS");
		return -1;
	}
	// a função retorna o ID da textbox.
	return ID;
}


int genChat(int pos[2], int siz[2], char *text, ALLEGRO_FONT *font, int ID)
{
	// a função ou recebe ou desenha uma caixa no display
	// esta caixa deve ser to tipo textbox
	// se a caixa existir deve-se apenas dar um update no texto.
	// negativo para inexistência
	if (ID < 0)
	{
		ID = genBox();
		if( ID < 0)
			return -1; // não achou blocos livres
	}
	else if (!box[ID].existe)
	{
		printf("\nALTERANDO VALORES DE UMA CAIXA INEXISTENTE");
	}
	// se achou deve alterar os conteúdos.
	memcpy(box[ID].pos, pos, 2);
	memcpy(box[ID].siz, siz, 2);
	box[ID].type = 1;

	// e gerar um texto para o interior.
	box[ID].texto = true;
	box[ID].text = text;
	box[ID].font = font;

	printf("\nCAIXA DE ID.%d SETTADA", ID);
	return ID;
	// a função retorna o ID da textbox gerada
}


int main(void)
{
	// !!!______SETUP______!!!
	// Inicialização e análise de erro 
	printf("\nEXECUTANDO MAIN\n");
	if (!setup())
	{
		printf("\nAbortando execução");
		return -1;
	}
	
	// Inicialização das estruturas ALLEGRO
	ALLEGRO_DISPLAY   *display = al_create_display(width, height);
	ALLEGRO_TIMER       *timer = al_create_timer(1.0 / 30.0);
	ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();

	// Adição de fontes
	ALLEGRO_FONT *SANS18 = 
	al_load_font("fonts/OpenSans-Bold.ttf", 18, 0);
	
	if(!display || !timer || !queue)
	{
		printf("\n Estruturas ALLEGRO não inicializadas");
		return -1;
	}

	// Registro dos eventos ALLEGRO
	{
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_keyboard_event_source());
	}

	// Inicialização do jogo
	bool chatexample = true; // experimental

	bool pausado = false; // deve ser int para indicar para o quê está pausado
	bool rodando = true;

	al_start_timer(timer);
	while (rodando)
	{
		//limpa a tela
		al_clear_to_color(al_map_rgb(200,200,200));
		ALLEGRO_EVENT evento;

		//espera um evento
		al_wait_for_event(queue, &evento);

		//encerração do programa
		if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			rodando = false;
		}
		else
		{
			//renderiza a tela aqui

			 if (pausado) //PAUSADO
			{
				// analisa o pause
			}
			else //NORMAL
			{
				// o jogo roda normalmente
				// módulo de exemplo
				if(chatexample)
				{
				//TESTE!!!!
				int pos[] = {width/2, height/2};
				int siz[] = {300, 400};
				if (genChat(pos, siz,"TEST", SANS18, -1) < 0)
					chatexample = false;
				}
				//inicia uma caixa de comentários de ID 1.
			}
		}
		al_flip_display();
	}

	al_destroy_event_queue(queue);
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_uninstall_keyboard();
	printf("\n");
}

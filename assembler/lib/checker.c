#include "checker.h"

Label *jumper, *variable;

void getJumpers(Line *line);

void getVariables(Line *line);

int check(Line *line) {
	Line *aux = line;
	getJumpers(aux);

	aux = line;
	getVariables(aux);

	aux = line;
	while(aux != NULL && !strEquals(aux->text, ".pseg"))
		aux = aux->next;

	while((aux = aux->next) != NULL && aux->text[0] != '.') {
		int index = indexOf(aux->text, ':');
		char *instr = strOffset(aux->text, (index > -1) ? index+2 : 0);

		if(startWith(instr, "j ") || startWith(instr, "jt.") || startWith(instr, "jf.")) {
			char *label = strOffset(instr, indexOf(instr, ' ') + 1);

			Label *temp = jumper;
			int exist = 0;
			while(temp != NULL) {
				if(strEquals(temp->name, label)) {
					exist = 1;
					break;
				}
				temp = temp->next;
			}

			if(!exist) {
				printf("[C][ERRO] Destino nao encontrado: linha %d, Destino \"%s\"\n", aux->number, label);
				return 0;
			}
		} else if(startWith(instr, "lcl ") || startWith(instr, "lch ") || startWith(instr, "loadlit ")) {
			char *param = strOffset(instr, indexOf(instr, ',') + 1);
			if(startWith(param, "LOWBYTE ") || startWith(param, "HIGHBYTE ")) {
				char *label = strOffset(param, indexOf(param, ' ') + 1);

				Label *temp = jumper;
				int exist = 0;
				while(temp != NULL) {
					if(strEquals(temp->name, label)) {
						exist = 1;
						break;
					}
					temp = temp->next;
				}
				temp = variable;
				while(temp != NULL && !exist) {
					if(strEquals(temp->name, label)) {
						exist = 1;
						break;
					}
					temp = temp->next;
				}

				if(!exist) {
					printf("[C][ERRO] Label nao encontrado: linha %d, Label \"%s\"\n", aux->number, label);
					return 0;
				}
		    }
		}
	}

	return 1;
}

void getJumpers(Line *line) {
	Label *current = NULL;
	while(line != NULL && !strEquals(line->text, ".pseg"))
		line = line->next;

	while((line = line->next) != NULL && line->text[0] != '.') {
		int index = indexOf(line->text, ':');
		if(index > -1) {
			char *name = substring(line->text, 0, index - 1);
			if(current == NULL) {
				jumper = malloc(sizeof(Label));
                jumper->name = name;
                jumper->next = NULL;
                current = jumper;
            } else {
                current->next = malloc(sizeof(Label));
                current = current->next;
                current->name = name;
                current->next = NULL;
            }
		}
	}
}

void getVariables(Line *line) {
	Label *current = NULL;
	while(line != NULL && !strEquals(line->text, ".dseg"))
		line = line->next;

	if(line == NULL) return; //Não tem .dseg

	while((line = line->next) != NULL && (line->text[0] != '.' || startWith(line->text, ".word"))) {
		int index = indexOf(line->text, ':');
		if(index > -1) {
			char *name = substring(line->text, 0, index - 1);
			if(current == NULL) {
				variable = malloc(sizeof(Label));
                variable->name = name;
                variable->next = NULL;
                current = variable;
            } else {
                current->next = malloc(sizeof(Label));
                current = current->next;
                current->name = name;
                current->next = NULL;
            }
		}
	}
}
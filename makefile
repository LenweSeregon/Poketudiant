CC = gcc
CFLAGS = -ansi -pedantic -Wall -Wextra -g

S = ./src
I = ./include
B = ./bin

OBJS = 			$(B)/main.o\
			$(B)/linked_list.o\
			$(B)/hash_table.o\
			$(B)/container.o\
			$(B)/poketudiant.o\
			$(B)/attack.o\
			$(B)/type_poke.o\
			$(B)/string_utils.o\
			$(B)/loading_module.o\
			$(B)/math_utils.o\
			$(B)/generic_control_function.o\
			$(B)/factories.o\
			$(B)/evolve_module.o\
			$(B)/pokecafetaria.o\
			$(B)/trainer.o\
			$(B)/battle_module.o\
			$(B)/command_handler.o\
			$(B)/game.o\
			$(B)/weakness.o\
			$(B)/map.o

executable : 		$(OBJS)
	$(CC) -o $@ $^ -lm

$(B)/main.o : 		$(S)/main.c\
			$(I)/constantes.h\
			$(I)/game.h\
			$(I)/math_utils.h\
			$(I)/string_utils.h\
			$(I)/container.h\
			$(I)/linked_list.h\
			$(I)/hash_table.h\
			$(I)/type_poke.h\
			$(I)/attack.h\
			$(I)/poketudiant.h\
			$(I)/pokecafetaria.h\
			$(I)/trainer.h\
			$(I)/generic_control_function.h\
			$(I)/loading_module.h\
			$(I)/evolve_module.h\
			$(I)/factories.h\
			$(I)/battle_module.h\
			$(I)/map.h
	$(CC) $(CFLAGS) -c $< -I $(I) -o $@

$(B)/map.o:		$(S)/map.c\
			$(I)/constantes.h\
			$(I)/string_utils.h\
			$(I)/map.h
	$(CC) $(CFLAGS) -c $< -I $(I) -o $@

$(B)/game.o:		$(S)/game.c\
			$(I)/constantes.h\
			$(I)/game.h\
			$(I)/math_utils.h\
			$(I)/string_utils.h\
			$(I)/container.h\
			$(I)/linked_list.h\
			$(I)/hash_table.h\
			$(I)/type_poke.h\
			$(I)/attack.h\
			$(I)/poketudiant.h\
			$(I)/pokecafetaria.h\
			$(I)/trainer.h\
			$(I)/generic_control_function.h\
			$(I)/loading_module.h\
			$(I)/evolve_module.h\
			$(I)/factories.h\
			$(I)/battle_module.h\
			$(I)/command_handler.h\
			$(I)/weakness.h\
			$(I)/map.h
	$(CC) $(CFLAGS) -c $< -I $(I) -o $@

$(B)/command_handler.o:	$(S)/command_handler.c\
			$(I)/constantes.h\
			$(I)/command_handler.h\
			$(I)/game.h\
			$(I)/math_utils.h\
			$(I)/string_utils.h\
			$(I)/container.h\
			$(I)/linked_list.h\
			$(I)/hash_table.h\
			$(I)/type_poke.h\
			$(I)/attack.h\
			$(I)/poketudiant.h\
			$(I)/pokecafetaria.h\
			$(I)/trainer.h\
			$(I)/generic_control_function.h\
			$(I)/loading_module.h\
			$(I)/evolve_module.h\
			$(I)/factories.h\
			$(I)/battle_module.h
	$(CC) $(CFLAGS) -c $< -I $(I) -o $@

$(B)/battle_module.o :	$(S)/battle_module.c\
			$(I)/constantes.h\
			$(I)/battle_module.h\
			$(I)/string_utils.h\
			$(I)/math_utils.h\
			$(I)/container.h\
			$(I)/linked_list.h\
			$(I)/hash_table.h\
			$(I)/type_poke.h\
			$(I)/attack.h\
			$(I)/poketudiant.h\
			$(I)/trainer.h\
			$(I)/factories.h\
			$(I)/game.h\
			$(I)/weakness.h
	$(CC) $(CFLAGS) -c $< -I $(I) -o $@

$(B)/evolve_module.o : 	$(S)/evolve_module.c\
			$(I)/constantes.h\
			$(I)/evolve_module.h\
			$(I)/math_utils.h\
			$(I)/container.h\
			$(I)/linked_list.h\
			$(I)/hash_table.h\
			$(I)/type_poke.h\
			$(I)/attack.h\
			$(I)/poketudiant.h\
			$(I)/generic_control_function.h
	$(CC) $(CFLAGS) -c $< -I $(I) -o $@

$(B)/factories.o : 	$(S)/factories.c\
			$(I)/constantes.h\
			$(I)/factories.h\
			$(I)/math_utils.h\
			$(I)/linked_list.h\
			$(I)/hash_table.h\
			$(I)/attack.h\
			$(I)/poketudiant.h\
			$(I)/generic_control_function.h\
			$(I)/container.h\
			$(I)/type_poke.h
	$(CC) $(CFLAGS) -c $< -I $(I) -o $@

$(B)/loading_module.o : $(S)/loading_module.c\
			$(I)/constantes.h\
			$(I)/loading_module.h\
			$(I)/type_poke.h\
			$(I)/string_utils.h\
			$(I)/poketudiant.h\
			$(I)/attack.h\
			$(I)/weakness.h\
			$(I)/hash_table.h 
	$(CC) $(CFLAGS) -c $< -I $(I) -o $@


$(B)/generic_control_function.o : \
			$(S)/generic_control_function.c\
			$(I)/constantes.h\
			$(I)/generic_control_function.h\
			$(I)/attack.h\
			$(I)/type_poke.h\
			$(I)/poketudiant.h
	$(CC) $(CFLAGS) -c $< -I $(I) -o $@

$(B)/trainer.o :	$(S)/trainer.c\
			$(I)/constantes.h\
			$(I)/trainer.h\
			$(I)/type_poke.h\
			$(I)/attack.h\
			$(I)/poketudiant.h\
			$(I)/generic_control_function.h\
			$(I)/pokecafetaria.h
	$(CC) $(CFLAGS) -c $< -I $(I) -o $@

$(B)/poketudiant.o : 	$(S)/poketudiant.c\
			$(I)/constantes.h\
			$(I)/poketudiant.h\
			$(I)/type_poke.h\
			$(I)/attack.h
	$(CC) $(CFLAGS) -c $< -I $(I) -o $@

$(B)/attack.o : 	$(S)/attack.c\
			$(I)/constantes.h\
			$(I)/attack.h\
			$(I)/type_poke.h
	$(CC) $(CFLAGS) -c $< -I $(I) -o $@

$(B)/weakness.o : 	$(S)/weakness.c\
			$(I)/constantes.h\
			$(I)/weakness.h\
			$(I)/type_poke.h
	$(CC) $(CLAGS) -c $< -I $(I) -o $@

$(B)/type_poke.o : 	$(S)/type_poke.c\
			$(I)/type_poke.h
	$(CC) $(CFLAGS) -c $< -I $(I) -o $@


$(B)/hash_table.o: 	$(S)/hash_table.c\
			$(I)/constantes.h\
			$(I)/hash_table.h\
			$(I)/linked_list.h\
			$(I)/container.h\
			$(I)/math_utils.h
	$(CC) $(CFLAGS) -c $< -I $(I) -o $@

$(B)/linked_list.o : 	$(S)/linked_list.c\
			$(I)/constantes.h\
			$(I)/linked_list.h\
			$(I)/container.h
	$(CC) $(CFLAGS) -c $< -I $(I) -o $@

$(B)/container.o : 	$(S)/container.c\
			$(I)/constantes.h\
			$(I)/container.h
	$(CC) $(CFLAGS) -c $< -I $(I) -o $@

$(B)/math_utils.o :	$(S)/math_utils.c\
			$(I)/constantes.h\
			$(I)/math_utils.h
	$(CC) $(CFLAGS) -c $< -I $(I) -o $@ 

$(B)/string_utils.o : 	$(S)/string_utils.c\
			$(I)/constantes.h\
			$(I)/string_utils.h
	$(CC) $(CFLAGS) -c $< -I $(I) -o $@

$(B)/pokecafetaria.o :	$(S)/pokecafetaria.c\
			$(I)/constantes.h\
			$(I)/type_poke.h\
			$(I)/attack.h\
			$(I)/poketudiant.h\
			$(I)/pokecafetaria.h
	$(CC) $(CFLAGS) -c $< -I $(I) -o $@ 

clean :
	@rm -rf $(B)/* 2>/dev/null || true
	@rm -rf $(B)/*.*~ 2>/dev/null || true
	@rm -rf $(S)/*.*~ 2>/dev/null || true
	@rm -rf $(I)/*.*~ 2>/dev/null || true
	@rm -rf *~ 2>/dev/null || true

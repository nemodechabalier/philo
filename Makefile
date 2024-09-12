# Nom de l'exécutable
NAME = philo

# Répertoires
SRCDIR = srcs
OBJDIR = objs

# Fichiers sources et objets
SRC = $(SRCDIR)/main.c $(SRCDIR)/philo_utils.c $(SRCDIR)/one_philo.c $(SRCDIR)/thread_verif.c $(SRCDIR)/routine.c $(SRCDIR)/thread_mutex_utils.c
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Options de compilation
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
RM = rm -f



# Création de l'exécutable
$(NAME): $(OBJ)
	@echo "\033[1;32mLinking objects...\033[0m"
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "\033[1;32mCompilation terminée avec succès ! 🎉\033[0m"

# Règle par défaut
all: $(NAME)

# Compilation des fichiers objets
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@echo "\033[1;34mCompilation de $<...\033[0m"
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "\033[1;32mFichier objet $@ créé avec succès !\033[0m"

# Nettoyage des fichiers objets
clean:
	@echo "\033[1;33mNettoyage des fichiers objets...\033[0m"
	$(RM) $(OBJ)
	$(RM) -r $(OBJDIR)
	@echo "\033[1;32mNettoyage terminé.\033[0m"

# Nettoyage complet (fichiers objets et exécutable)
fclean: clean
	@echo "\033[1;33mSuppression de l'exécutable...\033[0m"
	$(RM) $(NAME)
	@echo "\033[1;32mSuppression complète effectuée.\033[0m"

# Recompilation complète
re: fclean all

# Éviter les conflits avec des fichiers qui portent les mêmes noms que les cibles Makefile
.PHONY: all clean fclean re 

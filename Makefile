# Makefile du projet Morpion

CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -pedantic -Iinclude

SRC_DIR   = src
TEST_DIR  = tests
BUILD_DIR = build

EXEC      = morpion
EXEC_TEST = test_morpion

HEADERS = $(wildcard include/*.h)

# Fichiers objets du jeu
OBJETS = $(BUILD_DIR)/Plateau.o $(BUILD_DIR)/Joueur.o $(BUILD_DIR)/JoueurHumain.o \
         $(BUILD_DIR)/JoueurIA.o $(BUILD_DIR)/Jeu.o $(BUILD_DIR)/main.o

# Fichiers objets des tests (sans main.cpp ni saisie clavier)
OBJETS_TEST = $(BUILD_DIR)/Plateau.o $(BUILD_DIR)/Joueur.o $(BUILD_DIR)/JoueurIA.o \
              $(BUILD_DIR)/tests.o

.PHONY: all clean run test

# Compile le jeu et les tests
all: $(EXEC) $(EXEC_TEST)

$(EXEC): $(OBJETS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJETS)

$(EXEC_TEST): $(OBJETS_TEST)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJETS_TEST)

# Compilation des fichiers du dossier src
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilation du fichier de tests
$(BUILD_DIR)/tests.o: $(TEST_DIR)/tests.cpp $(HEADERS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Lance le jeu
run: $(EXEC)
	./$(EXEC)

# Lance les tests
test: $(EXEC_TEST)
	./$(EXEC_TEST)

# Supprime les fichiers compilés
clean:
	rm -rf $(BUILD_DIR) $(EXEC) $(EXEC_TEST)

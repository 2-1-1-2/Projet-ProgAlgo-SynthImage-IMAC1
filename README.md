# Projet-ProgAlgo-SynthImage-IMAC1

Pour installer la bibliothèque SOIL:

sudo apt-get install libglu1-mesa-dev libglfw3-dev

Télécharger la librairie SOIL:
git clone https://github.com/DeVaukz/SOIL.git

Accéder au répertoire nouvellement créé:
cd SOIL

cmake .

make

sudo make install

Ajoutez le chemin du répertoire contenant libSOIL.so.1 à la variable d'environnement LD_LIBRARY_PATH de manière temporaire (à faire dès qu'on ouvre un terminal). Vous pouvez le faire en exécutant la commande suivante dans un terminal :

export LD_LIBRARY_PATH=/usr/local/lib:${LD_LIBRARY_PATH}

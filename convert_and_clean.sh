#!/bin/bash

# Dossier contenant les fichiers à traiter
input_dir="/Users/user/Downloads/output"
output_dir="/Users/user/Downloads/converted"

# Créer un répertoire de sortie pour les fichiers convertis
mkdir -p "$output_dir"

# Boucle sur tous les fichiers du répertoire
for file in "$input_dir"/*; do
  # Vérifier si c'est un fichier (et non un répertoire)
  if [[ -f "$file" ]]; then
    # Vérification de l'encodage du fichier
    encoding=$(file -bi "$file" | sed 's/.*charset=\(.*\)/\1/')

    # Afficher l'encodage détecté
    echo "Fichier: $file | Encodage détecté: $encoding"

    # Si l'encodage est "regular file", ou vide, essayer avec ISO-8859-1
    if [[ "$encoding" == "regular file" || -z "$encoding" ]]; then
      echo "$file n'a pas un encodage valide détecté. On essaie avec ISO-8859-1."
      encoding="ISO-8859-1"
    fi

    # Si l'encodage est déjà UTF-8, on passe au suivant
    if [[ "$encoding" == "utf-8" ]]; then
      echo "$file déjà en UTF-8, pas de conversion nécessaire"
    else
      echo "Conversion de $file en UTF-8 avec l'encodage $encoding"

      # Conversion du fichier en UTF-8 avec iconv
      iconv -f "$encoding" -t utf-8 "$file" > "$output_dir/$(basename "$file")"

      # Vérifier si la conversion a réussi
      if [[ $? -eq 0 ]]; then
        rm "$file"
        echo "$file supprimé après conversion"
      else
        echo "Erreur lors de la conversion de $file avec l'encodage $encoding"
      fi
    fi
  else
    echo "$file est un répertoire, il est ignoré"
  fi
done

echo "Traitement terminé."
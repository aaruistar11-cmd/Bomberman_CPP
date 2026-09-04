#!/bin/bash
echo "Sto installando Git per poter caricare il progetto su GitHub..."
echo "Inserisci la tua password:"
sudo apt-get update
sudo apt-get install -y git
echo "=========================================="
echo "Installazione di Git completata! Chiudi pure questa finestra."
echo "=========================================="
read -p "Premi INVIO per uscire..."

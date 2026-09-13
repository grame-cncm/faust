#!/bin/bash

# Script de test pour le profiling de eval.cpp

echo "=========================================="
echo "Test du profiling de eval.cpp"
echo "=========================================="
echo ""

# Vérifier que faust est compilé
if [ ! -f "../../faust" ]; then
    echo "Erreur: Le compilateur faust n'est pas trouvé à ../../faust"
    echo "Veuillez compiler faust d'abord avec 'make'"
    exit 1
fi

# Créer un fichier de test simple
TEST_DSP=$(mktemp /tmp/test_profiling_XXXXXX.dsp)
cat > "$TEST_DSP" << 'EOF'
import("stdfaust.lib");

// Simple test avec quelques opérations
process = no.noise : fi.lowpass(4, 1000) : ef.echo(0.5, 0.5, 0.5);
EOF

echo "Fichier de test créé: $TEST_DSP"
echo ""
echo "Contenu du fichier:"
cat "$TEST_DSP"
echo ""
echo "=========================================="
echo "Compilation SANS profiling"
echo "=========================================="
echo ""

time ../../faust -lang cpp -o /tmp/test_out.cpp "$TEST_DSP" 2>&1 | head -20

echo ""
echo "=========================================="
echo "Compilation AVEC profiling"
echo "=========================================="
echo ""

FAUST_PROFILE_EVAL=1 time ../../faust -lang cpp -o /tmp/test_out_profiled.cpp "$TEST_DSP" 2>&1

echo ""
echo "=========================================="
echo "Test terminé"
echo "=========================================="

# Nettoyer
rm -f "$TEST_DSP" /tmp/test_out.cpp /tmp/test_out_profiled.cpp

echo ""
echo "Pour utiliser le profiling avec vos fichiers:"
echo "  FAUST_PROFILE_EVAL=1 faust yourfile.dsp"

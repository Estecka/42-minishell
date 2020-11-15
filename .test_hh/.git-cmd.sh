# --------------------------------------------------------------------------#
# git stash stocke (ou stashe) temporairement les changements apportés
git stash -u
# --------------------------------------------------------------------------#
# Récupére toutes les données des commits effectués sur la branche courante 
# qui n'existent pas encore dans votre version en local
git fetch --prune
# --------------------------------------------------------------------------#
# Intègre les modifications des commits nommés dans la branche actuelle
git merge origin/master
# --------------------------------------------------------------------------#
# Réapplique les changements stashés au préalable
#git stash pop
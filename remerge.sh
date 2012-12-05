#!/bin/sh
git remote add gtkradiant git://github.com/TTimo/GtkRadiant.git
git remote add q2 git@github.com:slapin/Quake-2.git
git remote add q2game git@github.com:slapin/quake2-game-so.git
git remote add netradiant git://git.icculus.org/divverent/netradiant.git
git remote add netradiant2 git://github.com/clbr/netradiant.git
git remote add netradiant3 git://github.com/divVerent/NetRadiant.git
git remote add q2tools git://github.com/id-Software/Quake-2-Tools
git remote update

git merge -s subtree q2/master
git merge -s subtree q2game/master
git merge -s subtree gtkradiant/master
git merge -s subtree netradiant/master
git merge -s subtree netradiant2/master
git merge -s subtree netradiant3/master
git merge -s subtree q2tools/master


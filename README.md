# Etrian Odyssey V Skill Simulator
_EOV / EO5 Skill Sim for desktop._ 

This is one of my first sizeable projects in C++, Qt, and git. I hope nevertheless with EO5's release pending the community enjoys some benefit as I learn and flesh out the project. The simulator is satisfactorily functional, but may have some early stage bugs if one hunts deeply enough.

## Use
The simulator allows you to allocate and visualize your character's Skill Point distribution for a set Race, Class, Mastery, and level. Clicking on a skill or adjusting a parameter will display the Skill's details. Most impossible combinations (i.e. Skill requirements not being met, Master Skills at a low level) should correct themselves. When satisfied, File -> Export Character will save your build to a text file.

# To-Do
### Priority
* Class skill trees emulate in-game tree shapes, albeit with minor(yet infuriating) alignment issues. Connecting lines for pre-requisites still needed.
* Race skills tab is serviceably basic, but ugly. 

### Minor
* Bug (Feature?) - Skill Points can allocate into negative if exceeding the total from Lv. 99!99.
* Switch tab focus on Race or Class change to appropriate tab.
* Info dialog for Damage formulae.
* Consistent descriptions for Skills, may need the game's release for complete information.
* Clarity for Defense/Damage modifiers for Skills.
* Complete stat usage for Master and Race Skills.
* Import function for saved builds.
* Easier means of allocating points?
* Info dialog for stat totals?

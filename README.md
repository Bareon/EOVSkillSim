# Etrian Odyssey V Skill Simulator
_Desktop character skill simulator for Etrian Odyssey V._ 

This is one of my first sizeable projects in C++, Qt, and git. I hope nevertheless the community enjoys some benefit as I learn and flesh out the project. The simulator is satisfactorily functional, but still early stage bugs if one hunts deeply enough.

## Use
The simulator allows you to allocate and visualize your character's Skill Point distribution for a set Race, Class, Mastery, and level. Clicking on a skill or adjusting a parameter will display the Skill's details. Most impossible combinations (i.e. Skill requirements not being met, Master Skills at a low level) should correct themselves. When satisfied, File -> Export Character will save your build to a text file.

# To-Do
### Priority
* Complete the database. As of v0.1, only two Races (Earthlain, Therian) and two Classes (Fencer, Dragoon) are implemented.
* Create a more apparent visual for skill requirements and dependencies representative of the Skill tree

### Minor
* Skill Points will go into negative if exceeding the total from Lv. 99!99
* Race Skill allocation does not yet adjust to appropriate level if below threshold.
* Switch tab focus on Race or Class change to appropriate tab
* Consistent descriptions for Skills, may need the game's release for complete information
* Load function for saved builds
* Easier means of allocating points?

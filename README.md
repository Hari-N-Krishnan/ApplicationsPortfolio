Wordle Clone
____________


This project emulates the game "Wordle" in a terminal.
In this project, the contents of a dictionary of words are filtered out by length (5 letter words) and are stored in a string array. The program then picks a random word from the list of words and stores it as the "secret word".
The user tries to guess the secret word within 5 tries and clues are given to help narrow down on the correct word. The program properly emulates the behaviour found in Wordle in certain scenarios. For example, if the secret word was "infer" and the player 
guesses "radii" the letter 'r' is in the wrong place so it will get denoted as such and only one of the two "i's" will get marked as being in the wrong place and all the other letters will get marked as not being in the secret word.
The program also accounts for the player guess being illegal(say the player enters a 10 letter word, or a word which is not in the dictionary) and asks them to try again.


Unreal Engine 5 Slash Project
_____________________________

This project follows the course "Learn Unreal Engine 5 C++ Programming by Creating an Action-RPG Style Open World Game!" by Stephen Ulibarri in Udemy.
In this project, CPP classes are created for in-game blueprints such as for Items, Pawns, and Characters. The Item class contains code for an Item Blueprint in which the Item Mesh is set through the cpp class and the root component is set to the
Item mesh. The Item class also makes the item blueprint exhibit sinusoidal behaviour via the FMath struct functions which take into account variables such as Amplitdue and TimeConstant which are exposed to blueprint via the UPROPERTY macro. The 
item header file also has template function which calculates the average of two types(floats, doubles, integers or vectors) and can be used to draw debug points or spheres. There is also a debug macros header file in the projectwhich helps to
visualize the various vectors used in the program. The pawn class for the bird contains various classes which are forward declared in its header file which allow functionalities such EnhancedInput binding, Capsule creation, and the use of 
Spring Arms and Cameras with the approriate attachments set up via code itself. The mapping context which is used for enhanced input is also setup properly based on the player controller. Functionalities for moving the bird forward and backward 
are setup in the class and the rotation of the bird is taken into account for proper movement no matter where the camera is pointed. The bird gets auto possesed by the player at the start of the game is the blueprint is added into the active 
map. A similar class but for the player character Echo is setup which uses a lot of the similar functionalities but has additional movement like strafing left and right and groom components like hair and eyebrows. The character is also animation
supported in the class SlashAnimInstance which sets up things like Ground speed and checks whether the character is falling or not so that appropriate animations using state machines can be added in blueprint. Inverse Kinematics makes use of the 
aforementioned variables to simulate the character's skeletal mesh to behave in a semi-realistic manner instead of just floating awkwardly in slopes and inclines. 
The scope for this project is huge and further implementation of game mechanics like enemies, items and character attributes will be implemented as i progress further through the course.

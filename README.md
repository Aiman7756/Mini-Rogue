# Mini-Rogue
 A terminal-based dungeon crawling game featuring a variety of enemies, weapons, and spells. The goal of this game is to reach the bottom floor and retrieve the golden idol.
 
 ## Layout
 
 * The game consists of four floors. Every floor is a randomly generated layout consisting of four to six 'rooms' connected by corridors.
 
 * The first three floors generate a randomly placed staircase, used to descend to the next floor. The fourth floor has the golden idol instead of the staircase.
 
 * Item drops are randomly generated with each floor, with deeper floors being able to generate more dangerous monsters.

## Controls

* All controls corresponding to single keystrokes.

* **Arrow keys:** Move in the corresponding direction.

* **I:** Check inventory.

* **W:** Wield weapon— display the inventory, and then use a-z to choose a corresponding item.

* **R:** Read scroll— display the inventory, and then use a-z to choose a corresponding item.

* **G:** Grab item— pick up an item from the dungeon floor.

## Combat 

 * **Attacker Points:** are equal to the attacker's dex + the dex bonus granted by their weapon.
 
 * **Defender Points:** are equal to the defender's armor points + their dex.
 
 * **Hit chance:** A random number is chosen for the attacker, ranging from 1 to the value of the Attacker Points. Likewise for the defender with the max being the Defender points. If the attacker's random number is greater or equal to the defender's random number, then the attacker lands a successful hit.
 * **Damage:** The minimum damage is 0, and the max damage is the attacker's strength + the equipped weapon's damage bonus - 1. The damage is a random number between these two values.

## Inventory

* Players can hold a maximum of 26 weapons, including their currently equipped weapon.

* The inventory is displayed as a list, with items corresponding to letters a-z, so players can press the letter matching the item they want to interact with. Item A is always the current weapon.

 
 ## Monsters
 
   ### Bogeyman
 
  * **Display:** B
 
 * **HP:** 5-10, **Str:** 2-3, **Dex**: 2-3, **Armor:** 2
 
 * **Weapon:** Short Sword
 
 * **Movement:** If the player is within a 5x5 range, it will approach the player. Otherwise, there is no movement.
 
 * Can appear on every floor.
 
 * 1/10 chance to drop a weapon (Magic Axe)
 
 ### Snakewoman
 
 * **Display:** S
 
 * **HP:** 3-6, **Str:** 2, **Dex**: 3, **Armor:** 3
 
 * **Weapon:** Magic Fangs of Sleep
 
 * **Movement:** If the player is within a 3x3 range from the Snakewoman, it will approach the player. Otherwise, there is no movement.
 
 * Can appear on every floor.
 
  * 1/3 chance to drop Magic Fangs of Sleep
  
  ### Goblin
  
  * **Display:** G
 
 * **HP:** 15-20, **Str:** 3, **Dex**: 1, **Armor:** 1
 
 * **Weapon:** Short Sword
 
 * **Movement:** If the player is within a 15x15 range from the Goblin, it will approach the player. Otherwise, there is no movement.
 
 * Only appears on 3rd and 4th floors.
 
 * 1/3 chance to drop a weapon (Magic Fangs of Sleep or Magic Axe, equal chance)
 
 
 ### Dragon
 
  * **Display:** D
 
 * **HP:** 20-25, **Str:** 4, **Dex**: 4, **Armor:** 4
 
 * **Weapon:** Long Sword
 
 * **Movement:** Dragons do not approach the player, but they have a 1/10 chance to recover 1HP.
 
 * Only appears on 4th floor.
 
 * 100% chance to drop a scroll (any type)

## Weapons

**Display:** )

### Short Sword

* **Dex Bonus:** 0

* **Damage Bonus:** 2

### Long Sword

* **Dex Bonus:** 2

* **Damage Bonus:** 4

### Mace

* **Dex Bonus:** 0

* **Damage Bonus:** 2

### Magic Axe

* **Dex Bonus:** 5

* **Damage Bonus:** 5

### Magic Fangs of Sleep

* **Dex Bonus:** 3

* **Damage Bonus:** 2

* **Additional Effects:** 1/5 chance to put enemy to sleep for between 2 and 6 turns.


## Scrolls

**Display:** ?

### Scroll of Teleportation

* **Effect:** Teleports the player to a random set of coordinates on that floor.

### Scroll of Enhance Strength

* **Effect:** Increases the player's strength, between 1-3 points.

### Scroll of Enhance Dex

* **Effect:** Increases the player's dexterity by 1 point.

### Scroll of Enhance Armor

* **Effect:** Increases the player's armor points, between 1-3 points.

### Scroll of Enhance HP

* **Effect:** Increases the player's HP, between 3-8 points.

## Other

### Staircase

**Display:** >

### Golden Idol

**Display:** &
 

 
 
 
 

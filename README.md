# Mini-Rogue
 A terminal-based dungeon crawling game featuring a variety of enemies, weapons, and spells. The goal of this game is to reach the bottom floor and retrieve the golden idol.
 
 ## Layout
 
 * The game consists of four floors. Every floor is a randomly generated layout consisting of four to six 'rooms' connected by corridors.
 
 * The first three floors generate a randomly placed staircase, used to descend to the next floor. The fourth floor has the golden idol instead of the staircase.
 
 * Item drops are randomly generated with each floor, with deeper floors being able to generate rarer items are more dangerous monsters.
 
 ## Monsters
 
   ### Bogeyman
 
  * **Display:** B
 
 * **HP:** 5-10, **Str:** 2-3, **Dex**: 2-3, **Armor:** 2
 
 * **Weapon:** Short Sword
 
 * **Movement:** If the player is within a 5x5 range, it will approach the player. Otherwise, there is no movement.
 
 * Only appears on third and fourth floors.
 
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
 
 * Can appear on every floor.
 
 * 1/3 chance to drop a weapon (Magic Fangs of Sleep or Magic Axe, equal chance)
 
 
 ### Dragon
 
  * **Display:** D
 
 * **HP:** 20-25, **Str:** 4, **Dex**: 4, **Armor:** 4
 
 * **Weapon:** Long Sword
 
 * **Movement:** Dragons do not approach the player, but they have a 1/10 chance to recover 1HP.
 
 * Only appears on fourth floor.
 
 * 100% chance to drop a scroll (any type)

## Weapons

**Display:** B

### Short Sword

### Long Sword

### Mace

### Magic Axe

### Magic Fangs of Sleep


## Scrolls

**Display:** B

### Scroll of Teleportation

### Scroll of Enhance Strength

### Scroll of Enhance Dex

### Scroll of Enhance Armor

### Scroll of Enhance HP

## Other

### Staircase

**Display:** B

### Golden Idol

**Display:** B
 

 
 
 
 

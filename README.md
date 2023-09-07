A personal project for the processing of data on video game 'dragon ball: the breakers'.  This is a shoddy WIP, but is still fully functional.  
To use this app, download the 'DragonBallBreakers_WinData_exe folder.

the goal of this project was to provide a quick way to quantify and show statistics a player may want to know about their games.

This app does not track any information from the game, it instead reads a very specific textfile that a player keeps data on.  textfile must be named 'dblog.txt' and be in the origin folder.  An example of my own dblog is included in the project.

Once a dblog was made and some data was saved, simply click to recalculate stats and interact with the ui.  You can get stat information for any one raider or a combination of them.  Submit selection when you want to see the stats.


dblog must be made in a specific way for the program to interpret your data correctly.  Program reads 1 line at a time.  Any line of data not inputted with parsable information will not be included in the statistics.  You can replace any information with the - symbol if you don't wish to include it (or any single character of text), but information saved may vary on what you exclude.  

Include no spaces and only use tabs
Information kept is case sensitive
Data intake should be written as follows
For raiders (Cell, Frieza, Vegeta, Buu, Ginyu)
For account level (numbers between 1 - 100)
For raider win status (died, lived)
For raider cause of death (HP, STM, -)
For whether the STM was called (yes, no)
For level of raider when STM is called (numbers betwen 1 - 4)
For level of raider when game ends (numbers between 1 - 4)
For number of remaining survivors on STM called (numbers between 0 - 7)
For number of remaining survivors on game end (numbers between 0 - 7)
For shenron wishes include who wished (surv, raider, -)
For if the level 4 survivor is active at the end of the game (on, off, -)
For % of STM charged at the end of the game (numbers between 0 - 100)
For % of HP raider was left at end of the game (numbers between 0 - 100)
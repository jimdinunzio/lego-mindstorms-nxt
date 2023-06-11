// sound.c
/*
	Copyright (c) [2019] [James C DiNunzio, II]

	This file is part of TotalCanzRecall.
	TotalCanzRecall is free software: you can redistribute it and/or modify
  it under the terms of the Lesser GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  TotalCanzRecall is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with TotalCanzRecall.  If not, see <https://www.gnu.org/licenses/>.
*/

void playColorSound(int dotNumber)
{
	// Check the detected colour and display the name of the
  // color in a large font on the screen.
  switch(dotNumber)
  {
//    case BLACKCOLOR:
//      displayCenteredTextLine(6, "Black");
//      break;
  	case BLUECOLOR:
			//playSoundFile("BlueCan.rso");
  	//  displayCenteredBigTextLine(2, "Blue Can");
  	  break;
//    case GREENCOLOR:
//  		displayCenteredTextLine(6, "Green");
// 			break;
//    case YELLOWCOLOR:
//  		displayCenteredTextLine(6, "Yellow");
//  	break;
    case REDCOLOR:
    	//playSoundFile("RedCan.rso");
    	displayCenteredBigTextLine(2, "Red Can");
    	break;
    case WHITECOLOR:
    	//playSoundFile("WhiteCan.rso");
    	displayCenteredBigTextLine(2, "White Can");
    	break;
    default:
    	//playSoundFile("Woops.rso ");
    	displayCenteredBigTextLine(2, "I Missed.");
    	break;
  }
}

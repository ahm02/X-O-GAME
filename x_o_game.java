package xo;

import xo.Board;

import java.util.Scanner;
import java.util.Random;

public class x_o_game {


        public static void main(String[] args) {
            Board gameBoard = new Board();
            Random compChoice = new Random();
            char yourChar;
            char compChar;
            Scanner in = new Scanner(System.in);

            System.out.println("              TIC-TAC-TOE");
            System.out.println("CREATIVE COMPUTING  MORRISTOWN, NEW JERSEY");
            System.out.println("\nTHE BOARD IS NUMBERED: ");
            System.out.println(" 1  2  3\n 4  5  6\n 7  8  9\n");

            while (true) {

                System.out.println("DO YOU WANT 'X' OR 'O'");
                while (true) {
                    try {
                        char input;
                        input = in.next().charAt(0);

                        if (input == 'X' || input == 'x') {
                            yourChar = 'X';
                            compChar = 'O';
                            break;
                        } else if (input == 'O' || input == 'o') {
                            yourChar = 'O';
                            compChar = 'X';
                            break;
                        } else {
                            System.out.println("THAT'S NOT 'X' OR 'O', TRY AGAIN");
                            in.nextLine();
                        }

                    } catch (Exception e) {
                        System.out.println("THAT'S NOT 'X' OR 'O', TRY AGAIN");
                        in.nextLine();
                    }
                }

                while (true) {
                    System.out.println("WHERE DO YOU MOVE");


                    while (true) {
                        int input;
                        try {
                            input = in.nextInt();
                            if (gameBoard.getBoardValue(input) == ' ') {
                                gameBoard.setArr(input, yourChar);
                                break;
                            } else {
                                System.out.println("INVALID INPUT, TRY AGAIN");
                            }
                            in.nextLine();
                        } catch (Exception e) {
                            System.out.println("INVALID INPUT, TRY AGAIN");
                            in.nextLine();
                        }
                    }

                    gameBoard.printBoard();
                    System.out.println("THE COMPUTER MOVES TO");

                    while (true) {
                        int position = 1 + compChoice.nextInt(9);
                        if (gameBoard.getBoardValue(position) == ' ') {
                            gameBoard.setArr(position, compChar);
                            break;
                        }
                    }

                    gameBoard.printBoard();


                    if (gameBoard.checkWin(yourChar)) {
                        System.out.println("YOU WIN, PLAY AGAIN? (Y/N)");
                        gameBoard.clear();
                        while (true) {
                            try {
                                char input;
                                input = in.next().charAt(0);

                                if (input == 'Y' || input == 'y') {
                                    break;
                                } else if (input == 'N' || input == 'n') {
                                    System.exit(0);
                                } else {
                                    System.out.println("THAT'S NOT 'Y' OR 'N', TRY AGAIN");
                                    in.nextLine();
                                }

                            } catch (Exception e) {
                                System.out.println("THAT'S NOT 'Y' OR 'N', TRY AGAIN");
                                in.nextLine();
                            }
                        }
                        break;
                    } else if (gameBoard.checkWin(compChar)) {
                        System.out.println("YOU LOSE, PLAY AGAIN? (Y/N)");
                        gameBoard.clear();
                        while (true) {
                            try {
                                char input;
                                input = in.next().charAt(0);

                                if (input == 'Y' || input == 'y') {
                                    break;
                                } else if (input == 'N' || input == 'n') {
                                    System.exit(0);
                                } else {
                                    System.out.println("THAT'S NOT 'Y' OR 'N', TRY AGAIN");
                                    in.nextLine();
                                }

                            } catch (Exception e) {
                                System.out.println("THAT'S NOT 'Y' OR 'N', TRY AGAIN");
                                in.nextLine();
                            }
                        }
                        break;
                    } else if (gameBoard.checkDraw()) {
                        System.out.println("DRAW, PLAY AGAIN? (Y/N)");
                        gameBoard.clear();
                        while (true) {
                            try {
                                char input;
                                input = in.next().charAt(0);

                                if (input == 'Y' || input == 'y') {
                                    break;
                                } else if (input == 'N' || input == 'n') {
                                    System.exit(0);
                                } else {
                                    System.out.println("THAT'S NOT 'Y' OR 'N', TRY AGAIN");
                                    in.nextLine();
                                }

                            } catch (Exception e) {
                                System.out.println("THAT'S NOT 'Y' OR 'N', TRY AGAIN");
                                in.nextLine();
                            }
                        }
                        break;
                    }

                }
            }
        }
    }




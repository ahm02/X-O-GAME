import random
import sys


empty = " "
board = [empty] * 9
player_one = "X"
player_two = "O"


def draw_board(board: list) -> None:


    print("")

    for position in range(0, len(board), 3):

        print(f" {board[position]} | {board[position+1]} | {board[position+2]} ")

        if position != 6:
            print("---+---+---")


def empty_position(board: list, postion: int) -> bool:


    return True if board[postion] == empty else False


def valid_move(board: list, position: int, player: str) -> bool:

    if empty_position(board, position):

        board[position] = player
        return True

    return False


def check_winner(board: list) -> str:


    patterns = [
        [0, 1, 2],
        [3, 4, 5],
        [6, 7, 8],
        [0, 3, 6],
        [1, 4, 7],
        [2, 5, 8],
        [0, 4, 8],
        [2, 4, 6],
    ]

    for pattern in patterns:

        if board[pattern[0]] == board[pattern[1]] == board[pattern[2]] != empty:
            return board[pattern[0]]

    return empty


def print_winner(board: list) -> None:


    if check_winner(board) == player_one:
        print(f"\nPlayer {player_one} wins")

    elif check_winner(board) == player_two:
        print(f"\nPlayer {player_two} wins")

    elif check_winner(board) == empty:
        print("\n no one win!")


def random_positon() -> int:


    return random.randint(0, 8)


def best_position(board: list) -> int:


    available_positions = [
        x for x, letter in enumerate(board) if letter == empty and x != 0
    ]

    best_position = 0


    for let in [player_one, player_two]:

        for position in available_positions:
            board_copy = board.copy()
            board_copy[position] = let

            if check_winner(board_copy) == let:
                best_position = position
                return best_position


    corner_positions = [
        position for position in available_positions if position in [0, 2, 6, 8]
    ]

    if len(corner_positions) > 0:
        return random.choice(corner_positions)


    if 5 in available_positions:
        return 5


    edge_positions = [
        position for position in available_positions if position in [1, 3, 5, 7]
    ]

    if len(edge_positions) > 0:
        return random.choice(edge_positions)


def computer_move(board: list, player: str) -> int:


    position = best_position(board)

    if not valid_move(board, position, player):
        computer_move(board, player)
    else:
        print("\nComputer's move: ", position + 1)


def human_move(board: list, player: str) -> int:


    position = int(input("\nEnter a position: "))

    if position > 9 or position < 0:
        print("\nInvalid position")
        human_move(board, player)

    elif not valid_move(board, position - 1, player):
        print("\nInvalid position")
        human_move(board, player)


def play_game() -> None:

    for i in range(0, 9):
        if check_winner(board) != empty:
            break

        draw_board(board)

        if i % 2 == 0:
            human_move(board, player_one)
        else:
            computer_move(board, player_two)


def banner() -> None:

    print("\nTic Tac Toe")
    print(f"\nplayer_one is {player_one} and player_two is {player_two}")


def main() -> None:

    try:
        banner()
        play_game()
        draw_board(board)
        print_winner(board)

    except KeyboardInterrupt:
        print("\nGoodbye!")
        sys.exit()

    except Exception as e:
        print(e)


if __name__ == "__main__":
    main()
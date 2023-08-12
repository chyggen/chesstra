To build software:

download source, navigate to source directory <$SRC_DIR>. To install to <$INSTALL_DIR>, use:

    cd $SRC_DIR
    cmake -H. -Btmp_cmake -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR
    cmake --build tmp_cmake --clean-first --target install

To run a demonstration, use the command:

    $INSTALL_DIR/bin/demo

Once the display is on screen, use the following commands to operate the software:

    <square1> <square2> : moves a piece from square1 to square2 
    pgn                 : save the game to a pgn file in the current directory
    com <txt>           : adds a comment to the pgn file
    resign              : ends the game with a resignation for the active player
    draw                : ends the game with a draw agreement
    quit                : exits the application

by running the chesstra application with ./chesstra, several command line options can be used:

    -a              : autosaves a game pgn when quit is called
    -f <fenString>  : provides a FEN format position for the game to start from
    -w <name>       : provides a name for the white player in PGN exports
    -b <name>       : provides a name for the black player in PGN exports
    -e <name>       : provides an event name in PGN exports


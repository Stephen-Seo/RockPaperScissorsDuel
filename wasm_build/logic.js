Rune.initLogic({
    minPlayers: 2,
    maxPlayers: 2,
    setup: (players) => ({
        player1: players[0],
        player2: players[1],
        first_choices: new Array(3).fill(null),
        second_choices: new Array(3).fill(null),
        first_ready: false,
        second_ready: false,
        pos: 0,
    }),
    actions: {
        set_choices: (first, second, third, { game, playerId }) => {
            if (!game.first_ready || !game.second_ready) {
                throw Rune.invalidAction();
            }

            let is_first = game.player1 === playerId;

            function is_choices_filled(choices) {
                for (let i = 0; i < 3; ++i) {
                    if (choices[i] === null) {
                        return false;
                    }
                }
                return true;
            }

            if (is_choices_filled(is_first ? game.first_choices : game.second_choices)) {
                throw Rune.invalidAction();
            }

            function is_valid_choice(choice) {
                if (choice !== 'r' && choice !== 'p' && choice !== 's') {
                    return false;
                }
                return true;
            }

            if (!is_valid_choice(first) || !is_valid_choice(second)
                    || !is_valid_choice(third)) {
                throw Rune.invalidAction();
            }

            if (is_first) {
                game.first_choices[0] = first;
                game.first_choices[1] = second;
                game.first_choices[2] = third;
            } else {
                game.second_choices[0] = first;
                game.second_choices[1] = second;
                game.second_choices[2] = third;
            }


            if (!is_choices_filled(game.first_choices)
                    || !is_choices_filled(game.second_choices)) {
                return;
            }

            // Both sides are ready, iterate through matchups

            let has_remaining = false;

            for (let i = 0; i < 3; ++i) {
                // Get next matchup
                if (game.first_choices[i] === 'r'
                        || game.first_choices[i] === 'p'
                        || game.first_choices[i] === 's') {
                    // check if first won the matchup
                    if ((game.first_choices[i] === 'r' && game.second_choices[i] === 's')
                            || (game.first_choices[i] === 'p' && game.second_choices[i] === 'r')
                            || (game.first_choices[i] === 's' && game.second_choices[i] === 'p')) {
                        game.first_choices[i] = 'w';
                        game.second_choices[i] = 'l';
                        game.pos = game.pos + 1;
                    }
                    // check if second won the matchup
                    else if ((game.first_choices[i] === 'r' && game.second_choices[i] === 'p')
                            || (game.first_choices[i] === 'p' && game.second_choices[i] === 's')
                            || (game.first_choices[i] === 's' && game.second_choices[i] === 'r')) {
                        game.first_choices[i] = 'l';
                        game.second_choices[i] = 'w';
                        game.pos = game.pos - 1;
                    }
                    // matchup was a draw
                    else {
                        game.first_choices[i] = 'd';
                        game.second_choices[i] = 'd';
                    }
                    has_remaining = i === 2 ? false : true;
                }
            }

            game.first_ready = false;
            game.second_ready = false;
            if (!has_remaining) {
                if (game.pos <= -3) {
                    // second won
                    Rune.gameOver();
                } else if (game.pos >= 3) {
                    // first won
                    Rune.gameOver();
                } else {
                    // game is still going
                    for (let i = 0; i < 3; ++i) {
                        game.first_choices[i] = null;
                        game.second_choices[i] = null;
                    }
                }
            }
        },
        set_ready: ({ game, playerId }) => {
            let is_first = game.player1 === playerId;

            if (is_first) {
                game.first_ready = true;
            } else {
                game.second_ready = true;
            }
        },
    },
})

Rune.initLogic({
    minPlayers: 2,
    maxPlayers: 2,
    setup: (players) => ({
        player1: players[0],
        player2: players[1],
        first_choices: new Array(3).fill('?'),
        second_choices: new Array(3).fill('?'),
        ready: new Array(2).fill(false),
        pos: 0,
        matchup_idx: 0,
    }),
    actions: {
        set_choices: ({first, second, third}, { game, playerId }) => {
            if (!game.ready[0] || !game.ready[1]) {
                throw Rune.invalidAction();
            }

            let is_first = game.player1 === playerId;

            function is_choices_filled(choices) {
                for (let i = 0; i < 3; ++i) {
                    if (choices[i] === null || choices[i] === '?') {
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
        },
        set_ready: ({ is_ready }, { game, playerId }) => {
            let is_first = game.player1 === playerId;

            if (is_first) {
                game.ready[0] = is_ready;
            } else {
                game.ready[1] = is_ready;
            }
        },
        request_update: (unused, {game, playerId}) => {
            function is_choices_filled(choices) {
                for (let i = 0; i < 3; ++i) {
                    if (choices[i] === null || choices[i] === '?') {
                        return false;
                    }
                }
                return true;
            }

            if (!game.ready[0]
                    || !game.ready[1]
                    || !is_choices_filled(game.first_choices)
                    || !is_choices_filled(game.second_choices)) {
                return;
            }

            // Both sides are ready, iterate through matchups

            // check if first won the matchup
            if ((game.first_choices[game.matchup_idx] === 'r'
                        && game.second_choices[game.matchup_idx] === 's')
                    || (game.first_choices[game.matchup_idx] === 'p'
                        && game.second_choices[game.matchup_idx] === 'r')
                    || (game.first_choices[game.matchup_idx] === 's'
                        && game.second_choices[game.matchup_idx] === 'p')) {
                //game.first_choices[game.matchup_idx] = 'w';
                //game.second_choices[game.matchup_idx] = 'l';
                game.pos = game.pos + 1;
            }
            // check if second won the matchup
            else if ((game.first_choices[game.matchup_idx] === 'r'
                        && game.second_choices[game.matchup_idx] === 'p')
                    || (game.first_choices[game.matchup_idx] === 'p'
                        && game.second_choices[game.matchup_idx] === 's')
                    || (game.first_choices[game.matchup_idx] === 's'
                        && game.second_choices[game.matchup_idx] === 'r')) {
                //game.first_choices[game.matchup_idx] = 'l';
                //game.second_choices[game.matchup_idx] = 'w';
                game.pos = game.pos - 1;
            }
            // matchup was a draw
            //else {
                //game.first_choices[game.matchup_idx] = 'd';
                //game.second_choices[game.matchup_idx] = 'd';
            //}
            game.matchup_idx = game.matchup_idx + 1;

            game.ready[0] = false;
            game.ready[1] = false;
            if (game.matchup_idx >= 3) {
                if (game.pos <= -3) {
                    // second won
                    Rune.gameOver();
                } else if (game.pos >= 3) {
                    // first won
                    Rune.gameOver();
                } else {
                    // game is still going
                    for (let i = 0; i < 3; ++i) {
                        game.first_choices[i] = '?';
                        game.second_choices[i] = '?';
                    }
                    game.matchup_idx = 0;
                }
            }
        },
    },
})

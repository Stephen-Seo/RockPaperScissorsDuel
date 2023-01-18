Rune.initLogic({
    minPlayers: 2,
    maxPlayers: 2,
    setup: (players) => ({
        player1: players[0],
        player2: players[1],
        first_choices: new Array(3).fill('?'),
        second_choices: new Array(3).fill('?'),
        ready: new Array(2).fill(false),
        matchup_done: new Array(2).fill(false),
        pos: 0,
        prev_pos: 0,
        gameover: false,
        gameover_called: false,
        matchup_started: false,
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

            function check_matchup(a, b) {
                if (a == 'r') {
                    if (b == 'r') {
                        return 0;
                    } else if (b == 'p') {
                        return -1;
                    } else if (b == 's') {
                        return 1;
                    } else {
                        return 0;
                    }
                } else if (a == 'p') {
                    if (b == 'r') {
                        return 1;
                    } else if (b == 'p') {
                        return 0;
                    } else if (b == 's') {
                        return -1;
                    } else {
                        return 0;
                    }
                } else if (a == 's') {
                    if (b == 'r') {
                        return -1;
                    } else if (b == 'p') {
                        return 1;
                    } else if (b == 's') {
                        return 0;
                    } else {
                        return 0;
                    }
                } else {
                    return 0;
                }
            }

            if (is_choices_filled(game.first_choices) && is_choices_filled(game.second_choices)) {
                game.matchup_started = true;
                game.prev_pos = game.pos;
                for (let i = 0; i < 3; ++i) {
                    let result = check_matchup(game.first_choices[i], game.second_choices[i]);
                    if (result > 0) {
                        game.pos += 1;
                    } else if (result < 0) {
                        game.pos -= 1;
                    }

                    if (game.pos < -3 || game.pos > 3) {
                        game.gameover = true;
                        break;
                    }
                }

                if (game.pos <= -3 || game.pos >= 3) {
                    game.gameover = true;
                }
            }
        },
        set_ready: (unused, { game, playerId }) => {
            if (game.matchup_started) {
                throw Rune.invalidAction();
            }

            let is_first = game.player1 === playerId;

            if (is_first) {
                game.ready[0] = true;
            } else {
                game.ready[1] = true;
            }
        },
        set_matchup_done: (unused, { game, playerId }) => {
            let is_first = game.player1 === playerId;

            if (is_first) {
                game.matchup_done[0] = true;
            } else {
                game.matchup_done[1] = true;
            }

            if (game.matchup_done[0] && game.matchup_done[1]) {
                game.matchup_started = false;
                if (game.gameover) {
                    game.gameover_called = true;
                    Rune.gameOver();
                }

                game.ready[0] = false;
                game.ready[1] = false;
                game.matchup_done[0] = false;
                game.matchup_done[1] = false;
                game.first_choices[0] = '?';
                game.first_choices[1] = '?';
                game.first_choices[2] = '?';
                game.second_choices[0] = '?';
                game.second_choices[1] = '?';
                game.second_choices[2] = '?';
                game.prev_pos = game.pos;
            }
        },
    },
})

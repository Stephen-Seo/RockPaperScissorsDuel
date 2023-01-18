function do_rune_init() {
Rune.initClient({
    visualUpdate: ({ newGame, yourPlayerId}) => {
        const { player1, player2, first_choices, second_choices, ready, matchup_done, pos, prev_pos, gameover, gameover_called, matchup_started } = newGame;

        function is_choices_filled(choices) {
            for (let i = 0; i < 3; ++i) {
                if (choices[i] === null || choices[i] === '?') {
                    return false;
                }
            }
            return true;
        }

        if (is_choices_filled(first_choices) && is_choices_filled(second_choices)) {
            Module.ccall('game_visual_update',
                'number',
                ['string', 'string', 'string',
                    'number', 'number', 'number',
                    'number', 'number', 'number',
                    'boolean', 'boolean',
                    'boolean', 'boolean',
                    'number', 'number', 'boolean', 'boolean'],
                [player1, player2,
                    yourPlayerId === undefined ? 'undefined' : yourPlayerId,
                    first_choices[0].charCodeAt(0),
                    first_choices[1].charCodeAt(0),
                    first_choices[2].charCodeAt(0),
                    second_choices[0].charCodeAt(0),
                    second_choices[1].charCodeAt(0),
                    second_choices[2].charCodeAt(0),
                    ready[0], ready[1],
                    matchup_done[0], matchup_done[1],
                    pos, prev_pos, gameover_called, matchup_started]);
        } else {
            Module.ccall('game_visual_update',
                'number',
                ['string', 'string', 'string',
                    'number', 'number', 'number',
                    'number', 'number', 'number',
                    'boolean', 'boolean',
                    'boolean', 'boolean',
                    'number', 'number', 'boolean', 'boolean'],
                [player1, player2,
                    yourPlayerId === undefined ? 'undefined' : yourPlayerId,
                    '?'.charCodeAt(0),
                    '?'.charCodeAt(0),
                    '?'.charCodeAt(0),
                    '?'.charCodeAt(0),
                    '?'.charCodeAt(0),
                    '?'.charCodeAt(0),
                    ready[0], ready[1],
                    matchup_done[0], matchup_done[1],
                    pos, prev_pos, gameover_called, matchup_started]);
        }
    },
});
}

let em_checking_interval_id = setInterval(
    () => {
        if (Module != null && Module.ccall != null && Module.asm != null) {
            do_rune_init();
            clearInterval(em_checking_interval_id);
            console.log("Rune initialized!");
        }
    }, 500
);

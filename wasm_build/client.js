Rune.initClient({
    visualUpdate: ({ newGame, yourPlayerId}) => {
        const { player1, player2, first_choices, second_choices, ready, pos, matchup_idx } = newGame;

        Module.ccall('game_visual_update',
            undefined,
            ['string', 'string', 'string',
                'number', 'number', 'number',
                'number', 'number', 'number',
                'boolean', 'boolean',
                'number', 'number'],
            [player1, player2,
                yourPlayerId === undefined ? 'undefined' : yourPlayerId,
                first_choices[0].charCodeAt(0),
                first_choices[1].charCodeAt(0),
                first_choices[2].charCodeAt(0),
                second_choices[0].charCodeAt(0),
                second_choices[1].charCodeAt(0),
                second_choices[2].charCodeAt(0),
                ready[0], ready[1],
                pos, matchup_idx]);
    },
});

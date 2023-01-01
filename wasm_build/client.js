Rune.initClient({
    visualUpdate: ({ newGame, yourPlayerId}) => {
        const { player1, player2, first_choices, second_choices, first_ready, second_ready, pos } = newGame;

        Module.ccall('_game_visual_update',
            undefined,
            ['string', 'string', 'string',
                'number', 'number', 'number',
                'number', 'number', 'number',
                'boolean', 'boolean',
                'number'],
            [player1, player2, yourPlayerId === undefined ? 'undefined' : yourPlayerId,
                first_choices[0], first_choices[1], first_choices[2],
                second_choices[0], second_choices[1], second_choices[2],
                first_ready, second_ready,
                pos]);
    },
});

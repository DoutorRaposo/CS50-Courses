-- For this project, I'm using CRUD to specify.
-- This part is the CREATE from CRUD
INSERT INTO
    title (
        title,
        overview,
        release_date,
        poster_path,
        budget,
        revenue,
        runtime,
        status,
        tagline,
        certification
    )
VALUES
    (
        'The Shawshank Redemption',
        'Two imprisoned men bond over a number of years, finding solace and eventual redemption through acts of common decency.',
        '1994-10-14',
        '/q6y0Go1tsGEsmtFryDOJo3dEmqu.jpg',
        25000000,
        28341469,
        142,
        'Released',
        'Fear can hold you prisoner. Hope can set you free.',
        'R'
    );

INSERT INTO
    title (
        title,
        overview,
        release_date,
        poster_path,
        status,
        tagline,
        certification
    )
VALUES
    (
        'Inception',
        'A thief who enters the dreams of others to steal their secrets from their subconscious.',
        '2010-07-16',
        '/qmDpIHrmpJINaRKAfWQfftjCdyi.jpg',
        'Released',
        'Your mind is the scene of the crime.',
        'PG-13'
    );

INSERT INTO
    title (
        title,
        overview,
        release_date,
        poster_path,
        budget,
        revenue,
        runtime,
        status,
        tagline,
        certification
    )
VALUES
    (
        'The Dark Knight',
        'When the menace known as the Joker wreaks havoc and chaos on the people of Gotham, Batman must accept one of the greatest psychological and physical tests of his ability to fight injustice.',
        '2008-07-18',
        '/1hRoyzDtpgMU7Dz4JF22RANzQO7.jpg',
        185000000,
        1004558444,
        152,
        'Released',
        'Why So Serious?',
        'PG-13'
    );

-- This part is the READ from CRUD
SELECT
    *
FROM
    title;

SELECT
    title,
    release_date,
    runtime
FROM
    title;

SELECT
    title,
    release_date
FROM
    title
WHERE
    release_date > '2002-01-01';

SELECT
    *
FROM
    title_summary;

SELECT
    *
FROM
    title_summary
WHERE
    "title" = 'Inception';

-- This part is the UPDATE from CRUD
UPDATE
    title
SET
    revenue = 100000000
WHERE
    title = 'The Shawshank Redemption';

UPDATE
    title
SET
    status = 'Production'
WHERE
    title = 'Inception';

-- This part is the DELETE from CRUD
DELETE FROM
    title
WHERE
    title = 'Inception';
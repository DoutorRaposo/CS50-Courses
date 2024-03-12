CREATE TABLE `users` (
    `id` INT AUTO_INCREMENT,
    `first_name` VARCHAR(32) NOT NULL,
    `last_name` VARCHAR(32) NOT NULL,
    PRIMARY KEY(`id`)
);

CREATE TABLE `institutions` (
    `id` INT AUTO_INCREMENT,
    `institution_name` VARCHAR(64) NOT NULL,
    `type` VARCHAR(32) NOT NULL,
    `location` VARCHAR(64) NOT NULL,
    `foundation_year` SMALLINT,
    PRIMARY KEY(`id`)
);

CREATE TABLE `companies` (
    `id` INT AUTO_INCREMENT,
    `company_name` VARCHAR(32) NOT NULL,
    `company_area` VARCHAR(64) NOT NULL,
    `company_location` VARCHAR(64) NOT NULL,
    PRIMARY KEY(`id`)
);

CREATE TABLE `people_connections` (
    `id` INT AUTO_INCREMENT,
    `user_id_A` INT NOT NULL,
    `user_id_B` INT NOT NULL,
    PRIMARY KEY(`id`),
    FOREIGN KEY(`user_id_A`) REFERENCES `users`(`id`),
    FOREIGN KEY(`user_id_B`) REFERENCES `users`(`id`)
);

CREATE TABLE `school_connections` (
    `id` INT AUTO_INCREMENT,
    `user_id` INT NOT NULL,
    `start_affiliation` DATETIME NOT NULL,
    `end_affiliation` DATETIME,
    `degree` VARCHAR(32) NOT NULL,
    PRIMARY KEY(`id`),
    FOREIGN KEY(`user_id`) REFERENCES `users`(`id`)
);

CREATE TABLE `company_connections` (
    `id` INT AUTO_INCREMENT,
    `user_id` INT NOT NULL,
    `start_affiliation` DATETIME NOT NULL,
    `end_affiliation` DATETIME,
    `title` VARCHAR(32) NOT NULL,
    PRIMARY KEY(`id`),
    FOREIGN KEY(`user_id`) REFERENCES `users`(`id`)
);
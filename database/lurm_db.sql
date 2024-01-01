-- phpMyAdmin SQL Dump
-- version 5.1.1deb5ubuntu1
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: Jan 01, 2024 at 11:37 AM
-- Server version: 8.0.35-0ubuntu0.22.04.1
-- PHP Version: 8.1.2-1ubuntu2.14

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `lurm_db`
--

-- --------------------------------------------------------

--
-- Table structure for table `course`
--

CREATE TABLE `course` (
  `name` varchar(255) NOT NULL,
  `code` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Table structure for table `degrees`
--

CREATE TABLE `degrees` (
  `name` varchar(255) NOT NULL,
  `code` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Table structure for table `degree_courses`
--

CREATE TABLE `degree_courses` (
  `course_code` varchar(255) NOT NULL,
  `degree_code` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Table structure for table `institutions`
--

CREATE TABLE `institutions` (
  `name` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Table structure for table `institutions_degree`
--

CREATE TABLE `institutions_degree` (
  `name` varchar(255) NOT NULL,
  `degree_code` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE `users` (
  `SID` varchar(255) NOT NULL,
  `username` varchar(255) NOT NULL,
  `avatar` varchar(255) NOT NULL,
  `first_name` varchar(255) NOT NULL,
  `last_name` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Table structure for table `user_courses`
--

CREATE TABLE `user_courses` (
  `username` varchar(255) NOT NULL,
  `course_code` varchar(255) NOT NULL,
  `completed` tinyint(1) NOT NULL,
  `current` tinyint(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Table structure for table `user_degrees`
--

CREATE TABLE `user_degrees` (
  `username` varchar(255) NOT NULL,
  `degree_code` varchar(255) NOT NULL,
  `completed` tinyint(1) NOT NULL,
  `current` tinyint(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Table structure for table `user_institution`
--

CREATE TABLE `user_institution` (
  `username` varchar(255) NOT NULL,
  `institution_name` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `course`
--
ALTER TABLE `course`
  ADD PRIMARY KEY (`code`);

--
-- Indexes for table `degrees`
--
ALTER TABLE `degrees`
  ADD PRIMARY KEY (`code`);

--
-- Indexes for table `degree_courses`
--
ALTER TABLE `degree_courses`
  ADD KEY `course_code` (`course_code`),
  ADD KEY `degree_code` (`degree_code`);

--
-- Indexes for table `institutions`
--
ALTER TABLE `institutions`
  ADD PRIMARY KEY (`name`);

--
-- Indexes for table `institutions_degree`
--
ALTER TABLE `institutions_degree`
  ADD KEY `name` (`name`),
  ADD KEY `degree_code` (`degree_code`);

--
-- Indexes for table `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`username`);

--
-- Indexes for table `user_courses`
--
ALTER TABLE `user_courses`
  ADD KEY `username` (`username`),
  ADD KEY `course_code` (`course_code`);

--
-- Indexes for table `user_degrees`
--
ALTER TABLE `user_degrees`
  ADD KEY `username` (`username`),
  ADD KEY `degree_code` (`degree_code`);

--
-- Indexes for table `user_institution`
--
ALTER TABLE `user_institution`
  ADD KEY `username` (`username`),
  ADD KEY `institution_name` (`institution_name`);

--
-- Constraints for dumped tables
--

--
-- Constraints for table `degree_courses`
--
ALTER TABLE `degree_courses`
  ADD CONSTRAINT `degree_courses_ibfk_1` FOREIGN KEY (`course_code`) REFERENCES `course` (`code`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  ADD CONSTRAINT `degree_courses_ibfk_2` FOREIGN KEY (`degree_code`) REFERENCES `degrees` (`code`) ON DELETE RESTRICT ON UPDATE RESTRICT;

--
-- Constraints for table `institutions_degree`
--
ALTER TABLE `institutions_degree`
  ADD CONSTRAINT `institutions_degree_ibfk_1` FOREIGN KEY (`name`) REFERENCES `institutions` (`name`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  ADD CONSTRAINT `institutions_degree_ibfk_2` FOREIGN KEY (`degree_code`) REFERENCES `degrees` (`code`) ON DELETE RESTRICT ON UPDATE RESTRICT;

--
-- Constraints for table `user_courses`
--
ALTER TABLE `user_courses`
  ADD CONSTRAINT `user_courses_ibfk_1` FOREIGN KEY (`username`) REFERENCES `users` (`username`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  ADD CONSTRAINT `user_courses_ibfk_2` FOREIGN KEY (`course_code`) REFERENCES `course` (`code`) ON DELETE RESTRICT ON UPDATE RESTRICT;

--
-- Constraints for table `user_degrees`
--
ALTER TABLE `user_degrees`
  ADD CONSTRAINT `user_degrees_ibfk_1` FOREIGN KEY (`username`) REFERENCES `users` (`username`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  ADD CONSTRAINT `user_degrees_ibfk_2` FOREIGN KEY (`degree_code`) REFERENCES `degrees` (`code`) ON DELETE RESTRICT ON UPDATE RESTRICT;

--
-- Constraints for table `user_institution`
--
ALTER TABLE `user_institution`
  ADD CONSTRAINT `user_institution_ibfk_1` FOREIGN KEY (`username`) REFERENCES `users` (`username`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  ADD CONSTRAINT `user_institution_ibfk_2` FOREIGN KEY (`institution_name`) REFERENCES `institutions` (`name`) ON DELETE RESTRICT ON UPDATE RESTRICT;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
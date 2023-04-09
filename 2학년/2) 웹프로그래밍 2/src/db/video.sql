-- phpMyAdmin SQL Dump
-- version 5.0.2
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- 생성 시간: 20-12-25 17:34
-- 서버 버전: 10.4.14-MariaDB
-- PHP 버전: 7.4.9

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- 데이터베이스: `member`
--

-- --------------------------------------------------------

--
-- 테이블 구조 `video`
--

CREATE TABLE `video` (
  `num` int(11) NOT NULL,
  `link` text NOT NULL,
  `name` text NOT NULL DEFAULT '무제'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- 테이블의 덤프 데이터 `video`
--

INSERT INTO `video` (`num`, `link`, `name`) VALUES
(30, 'https://www.youtube.com/watch?v=m5ur2XwmsF8&feature=youtu.be', '1주차 1번강의'),
(31, 'https://www.youtube.com/watch?v=liRhc0r-09Y&feature=youtu.be', '1주차 2번 강의'),
(32, 'https://www.youtube.com/watch?v=5LsH5mawAMQ&feature=youtu.be', '1주차 3번강의'),
(33, 'https://www.youtube.com/watch?v=mrjciKS1IIg&feature=youtu.be', '1주차 4번강의'),
(34, 'https://www.youtube.com/watch?v=twl2yjYb1gY&feature=youtu.be', '2주차 1번강의'),
(35, 'https://www.youtube.com/watch?v=YNKBbxxm25s&feature=youtu.be', '2주차 2번강의'),
(37, 'https://www.youtube.com/watch?v=ZAVNkvn1frc&feature=youtu.be', '3주차 1번강의'),
(38, 'https://www.youtube.com/watch?v=jhRRGgvooJc&feature=youtu.be', '3주차 3번강의'),
(39, 'https://www.youtube.com/watch?v=xGMIoPKlz-o&feature=youtu.be', '4주차 1번강의'),
(40, 'https://www.youtube.com/watch?v=CNwzInUKNKE&feature=youtu.be', '4주차 2번강의'),
(41, 'https://www.youtube.com/watch?v=3M9Pn3VE7zA&feature=youtu.be', '5주차 1번강의'),
(42, 'https://www.youtube.com/watch?v=NLRUSX48UGI&feature=youtu.be', '6주차 1번강의'),
(43, 'https://www.youtube.com/watch?v=-42SXW--Ss0&feature=youtu.be', '6주차 2번강의'),
(44, 'https://www.youtube.com/watch?v=PhSrg8zgLwo&feature=youtu.be', '7주차 1번강의'),
(45, 'https://www.youtube.com/watch?v=lo5K81IrlJE&feature=youtu.be', '7주차 2번강의'),
(46, 'https://www.youtube.com/watch?v=R8NcX_tuqRk&feature=youtu.be', '9주차 1번강의'),
(47, 'https://www.youtube.com/watch?v=6UDfYx0H8Lk&feature=youtu.be', '9주차 2번강의'),
(48, 'https://www.youtube.com/watch?v=kVEFtc-MQgE&feature=youtu.be', '10주차 1번강의'),
(49, 'https://www.youtube.com/watch?v=EE25WJFNLU4&feature=youtu.be', '10주차 2번강의'),
(50, 'https://www.youtube.com/watch?v=TmK7uXoBr7s&feature=youtu.be', '11주차 1번강의'),
(51, 'https://www.youtube.com/watch?v=3qlGaI2AITc&feature=youtu.be', '12주차 1번강의'),
(52, 'https://www.youtube.com/watch?v=xgQLrw1ZCwM&feature=youtu.be', '12주차 2번강의'),
(53, 'https://www.youtube.com/watch?v=SNO_3eD04ns&feature=youtu.be', '13주차 2번강의'),
(54, 'https://www.youtube.com/watch?v=YnhMAKFzJ8s&feature=youtu.be', '14주차 1번강의'),
(55, 'https://www.youtube.com/watch?v=KR7d0tXEfWg&feature=youtu.be', '14주차 2번강의'),
(56, 'https://www.youtube.com/watch?v=d9CCwdd5YNg&feature=youtu.be', '14주차 3번강의'),
(57, 'https://www.youtube.com/watch?v=8CMiDVaIN4c&feature=youtu.be', '15주차 1번강의');

--
-- 덤프된 테이블의 인덱스
--

--
-- 테이블의 인덱스 `video`
--
ALTER TABLE `video`
  ADD PRIMARY KEY (`num`);

--
-- 덤프된 테이블의 AUTO_INCREMENT
--

--
-- 테이블의 AUTO_INCREMENT `video`
--
ALTER TABLE `video`
  MODIFY `num` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=58;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

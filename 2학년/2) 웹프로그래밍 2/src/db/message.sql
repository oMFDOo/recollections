-- phpMyAdmin SQL Dump
-- version 5.0.2
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- 생성 시간: 20-12-26 10:01
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
-- 데이터베이스: `mfdo`
--

-- --------------------------------------------------------

--
-- 테이블 구조 `message`
--

CREATE TABLE `message` (
  `num` int(11) NOT NULL,
  `send_id` char(20) NOT NULL,
  `rv_id` char(20) NOT NULL,
  `subject` char(200) NOT NULL,
  `content` text NOT NULL,
  `regist_day` char(20) DEFAULT NULL,
  `isRead` tinyint(1) DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- 테이블의 덤프 데이터 `message`
--

INSERT INTO `message` (`num`, `send_id`, `rv_id`, `subject`, `content`, `regist_day`, `isRead`) VALUES
(1, 'MFDO', 'ChaCha', '이건 테스트야!', '과연 내용이 잘 전달될 수 있을까? 너무 걱정이야!', '2020-12-17 (11:01)', 1),
(2, 'MFDO', 'ChaCha', '테스트야!', '내용이 잘 전달 되었으면 좋겠어ㅠㅠ', '2020-12-17 (11:04)', 1),
(3, 'MFDO', 'ChaCha', '테스트야!', '내용이 잘 전달 되었으면 좋겠어ㅠㅠ', '2020-12-17 (11:06)', 1),
(4, 'ChaCha', 'MFDO', 'RE: 테스트야!', '아 진짜 너무 신기하다\r\n\r\n-----------------------------------------------\r\n&gt; 내용이 잘 전달 되었으면 좋겠어ㅠㅠ', '2020-12-17 (11:17)', 1),
(5, 'MFDO', 'chacha', '안녕! 테스트 중이야!', '너에게 알림이 가고 있니?', '2020-12-26 (09:47)', 1),
(6, 'MFDO', 'MFDO', ' 쪽지 왔어요!', '내용을 확인하면! 메신저의 카운트와 [New] 표기가 사라져요!', '2020-12-26 (09:58)', 0);

--
-- 덤프된 테이블의 인덱스
--

--
-- 테이블의 인덱스 `message`
--
ALTER TABLE `message`
  ADD PRIMARY KEY (`num`);

--
-- 덤프된 테이블의 AUTO_INCREMENT
--

--
-- 테이블의 AUTO_INCREMENT `message`
--
ALTER TABLE `message`
  MODIFY `num` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

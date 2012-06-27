INSERT INTO `log` VALUES
(1, 'empty post', 0, '127.0.0.1', '2012-03-05 09:36:13', 0),
(2, 'auth failed', 0, '127.0.0.1', '2012-03-05 09:36:24', 0),
(3, 'empty post', 0, '127.0.0.1', '2012-03-05 09:37:02', 0),
(4, 'post', 2, '127.0.0.1', '2012-03-05 09:37:11', 1),
(5, 'post', 2, '127.0.0.1', '2012-03-05 09:37:58', 1),
(6, 'post', 2, '127.0.0.1', '2012-03-05 09:37:59', 1),
(7, 'post', 1, '127.0.0.1', '2012-03-05 09:38:00', 1),
(8, 'post', 1, '127.0.0.1', '2012-03-05 09:38:01', 1),
(9, 'post', 2, '127.0.0.1', '2012-03-05 10:17:26', 1);


INSERT INTO `point` (`id`, `latidude`, `longitude`, `attitude`, `speed`, `timestampUtc`, `receiver_id`) VALUES
(1, 42.3278, 11.0606,0, 0, '2012-01-13 19:21:00', 2),
(2, 42.3296, 11.0432,0, 0, '2012-01-13 19:24:00', 2),
(3, 42.3326, 11.0139,0, 0, '2012-01-13 19:29:00', 2),
(4, 42.335, 10.9874,0, 0, '2012-01-13 19:33:00', 2),
(5, 42.3379, 10.9658,0, 0, '2012-01-13 19:37:00', 2),
(6, 42.3675, 10.9254,0, 0, '2012-01-13 19:53:00', 2),
(7, 42.3703, 10.9255,0, 0, '2012-01-13 19:58:00', 2),
(8, 42.3717, 10.926,0, 0, '2012-01-13 20:02:00', 2);


INSERT INTO `receiver` (`name`,`apiKey`) VALUES
('drerscht','4cdqfTqhL4SswTTeA4sOL4SswTTeA4sO'),
('concordia', 'concordia');
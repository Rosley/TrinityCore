ALTER TABLE `creature`
	ADD COLUMN `canbedeleted` TINYINT(1) UNSIGNED NOT NULL DEFAULT '1' AFTER `dynamicflags`;
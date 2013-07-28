OAuth module allows to authenticate Drupal resources through the OAuth 1.0
protocol.

Since it relies in PECL's Oauth package, requests can also be signed with its
OAuth consumer component.

INSTALLATION
============

Read installation instructions on PECL's OAuth at
http://www.php.net/manual/en/install.pecl.php

Quick installation instructions for Linux users:

1. Run the following commands to install the library and its requirements.
sudo apt-get update
sudo apt-get install php-pear php5-dev
sudo pecl install oauth

2. Then add the OAuth extension to your php.ini file(s).
extension=oauth.so

3. Finally, restart your web server. In Apache you can do it with:
sudo service apache2 restart

USAGE
=====

TODO

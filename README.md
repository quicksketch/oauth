<h1>OAuth</h1>

OAuth implements the OAuth classes for use with Drupal and acts as a support
module for other modules that wish to use OAuth.

This module includes a slightly modified version of this 
<a rel="nofollow" href="http://oauth.googlecode.com/svn/code/php">
OAuth Client/Server library</a>

OAuth Client flow:

The callback to be used is /oauth/authorized/% where % is the id of the consumer
used by the client. We need the id of the consumer to be able to find the token
correctly.

<h2>Status</h2>

This Backdrop version of a Drupal contributed module is under development.


<h2>Installation</h2>

Install this module using the official Backdrop CMS instructions at https://backdropcms.org/guide/modules

Visit the configuration page under Administration > Configuration > Category > OAuth (admin/config/category/oauth)
and enter the required information.


<h2>License</h2>

This project is GPL v2 software. See the LICENSE.txt file in this directory for complete text.

<h2>Current Maintainers</h2>

<h3>For Drupal:</h3>
Juan Pablo Novillo Requena (juampy)
Kyle Browning (kylebrowning)
jobeirne
Pelle Wessman (voxpelli)
Hugo Wetterberg

<h3>Port to Backdrop:</h3>
Graham Oliver github.com/Graham-72


<h2>Credits</h2>
The Drupal module has been sponsored by Good Old, Mindpark and Lullabot.






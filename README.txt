Read Me (README.txt)
---------------------------------------------------------

 * Version 6.x-2.x
 * Contact: Bryan Lewellen (bryrock) (http://drupal.org/user/346823)
 *

Summary of Key Features in this version:

 * Logs work!
 * Session and cached Whitelisting works! (grants user access after passing a simple test)
 * Length of time cached visits are held are determined by configurable settings (not hard-coded values).
 * Default Views included (see blocked IPs with links to their Honeypot profiles)


IMPORTANT ADVISORY ABOUT THIS VERSION
-------------------------------------

This is a somewhat controversial version of httbl, so this advisory is to help you decide whether or not it is for you.

Historically there is at least one 6.x-1.x bug that has languished for over two years.  This is issue #570742 - "Logging is not working."  There is a fix for this bug, but it's the fix that is controversial.  It does fix there problem (and one other as well), but the controversy is over it's "expense" and whether or not it's worth it.

Here's a high level, plain language view of what this module does and why logging cannot work without the controversial solution:

	Httpbl's job is to keep unwanted visitors with disreputable IP addresses off of your Drupal site.  It does this by intercepting visitors as soon as they show up on the site, before a complete Drupal bootstrap has completed.  Httpbl essentially says, "Let's check out this visitor before we go through the trouble of starting up a Drupal session for them."
	
	It then checks to see if the visitor should be grey or blacklisted.  If the answer is yes to either of those conditions, httpbl tries to let us know by logging the event.  However, a problem then arises by virtue of the fact that logging services are yet available, because a full Drupal bootstrap has not yet completed.
	
	So, I contend that the only way to make logging work is to complete the bootstrap, and therein lies the controversy.  Some say that, at the least, it's too "expensive" to waste a bootstrap on an unwanted visitor.  I can wholeheartedly agree with that sentiment, but then logging is not even an option, so we'd just have to forget about logging.  Others have expressed concerns that this bootstrapping might have a detrimental effect on other modules or Drupal processes.  To that I can only say that I've been running my own fork of httpbl, with logging, on production sites for about two years, and this has never come up as an issue.  And, as far as there being the possibility of a cleaner solution available, maybe there is, but nobody has ever suggested one during the nearly two years this issue has been in the queue.
	
	Some have said that logging is not that big of a deal, so maybe the option should just be removed.  That's possible, but that alone will not get around the bootstrapping issue (and I'll get to why in a minute).  As to whether or not anyone really needs this logging capability, some feel that they do.  Even though the unwanted traffic that httpbl stops is most often non-human, robotic traffic, it does occasionally block real people, as it should, when they have compromised IP addresses found in the Project Honeypot database of nuisance traffic.  Depending on the application environment, when real people are blocked, they or others (important users, site admins, managers, executives, etc.) may feel the pressing need to know and/or explain why.  The logs can assist in validating and revealing the evidence that the blocked IP was correctly and appropriately blocked.  It allows you to say, "They were blocked because they're bad traffic.  That's what you wanted, right?"
	
	There is another, easier way to show who got blocked and why, and that too is included in this version of httpl.  It's a simple Views report that displays the cached data of blocked IPs, along with links to their Project Honeypot profiles (which explain why the IPs are unwanted).  This carries virtually no overhead expense at all.
	
	So, hey, great, then we don't really need the logging then, and don't have to do that "expensive" bootstrap, right?
	
	Wrong.
	
	Because there is another problem caused by the same condition of a less than complete bootstrap.  When httpl grey-lists an IP, it attempts to present a whitelist challenge to the user, which is a simple html form that will help detect whether or not they are human (and can read simple instructions).  It's been a long time so I'm short on some details, but I tested this functionality exhaustively in 2009, and I concluded that this function was, at best, unpredictable, or worse, didn't really work at all, and it all boiled down to the same "uncompleted bootstrapping" reason that crippled the logging function.
	
	So, here's what this version of httpl does:
	
	When a visitor should be blacklisted, it checks to see if we are logging, and if so it completes a bootstrap to allow that to happen.  Otherwise, if the logging option is not true, we don't bother with the bootstrap.
	
	When a visitor should be grey-listed, it completes a bootstrap regardless of whether or not logging is true, because it needs that completed cycle in order to properly present the white-listing challenge.
	
	Also, whether or not the logging option is true, in the unlikely event that the results retrieved from Project Honeypot are completely invalid, I contend that's a serious issue we need to know about, so a bootstrap cycle is completed in order to make it possible to log that error event.
	
	What this version does NOT do is cause an extra bootstrap every time it checks an IP.  No, it does not do that.  It only carries this extra expense in the conditions I stated above.
	
Bottom-line (should you use this or not)
----------------------------------------

For nearly two years I've been running my custom version of httpbl, that successfully logs and whitelists, on about a dozen sites that receive less than 10K visitors a month.  It typically greylists at least 4 visitors a day on each of these sites.  Blacklisting is rarer, about a handful in a week.  And though it is a rare event, I have received calls about somebody important being blocked, and when that happens the logs and the Views report make it easy to explain why to the caller's satisfaction.

If your site receives much more traffic, I still don't see this version doing any harm to your site, but it's possible that  the "expense" of that extra bootstrap could be noticeable if you're	absolutely getting hammered with bad IPs.  But I also contend that if that is happening, you've got other issues anyway, and you may need this module to help you do your detective work to find out why your site is a bad IP magnet.

Your options are:

	1 - Don't use this version (and forget about logs and predictable whitelisting).
	2 - Use this version with logging turned off and use the Views report to see who got blocked.  This mitigates the expense a little, but not completely.
	3 - Use this module in "comment checking" only mode.  Instead of keeping all bad visitors off your site completely, it just prevents them from leaving any comment spam, and then bans them from coming back.
	4 - Use this module to check all traffic, and be glad that any possible "expense" is keeping unwanted traffic off your site and can keep you informed as to why.
	       

A note about the future of httpbl (D7)
--------------------------------------

Thanks to updates in Drupal's API for 7 and beyond, the controversial bootstrapping mentioned above is not required to make logging work, so logging (including optional verbose logging for testing) will be entirely possible without any extra "expense."

In other words, httpbl 7x will be even better and less "expensive"

 
Bryrock

 
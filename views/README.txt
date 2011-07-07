Read Me (README.txt)
--------------------------------------------------------------------------------------------------------------

VIEWs for HTTPBL
----------------------

httpbl.views.inc 			- provides exposure of httpbl table to Views
httpbl.views_default.inc	- provides a simple default view/report of IPs blocked via Honeypot

------------
Views for HTTPBL Provided by:
  Bryan Lewellen (http://drupal.org/user/346823)

BASICS
--------------------------------------------
This view is disabled by default, so you must go to Views and enable it.

The report is available in the admin/reports
and is accessible to anyone with permission to see site reports.

In order to see this report,
some level of caching must be set in admin >> settings >> httpbl.

If "Database cache and Drupal access table" is set, then items shown
with a status of 1 should also be found in the access table, to be
removed in both tables when the expiry date has passed.

Items with a status of 2 are found only in the Database cache for httpbl, and
this also would apply to status 1 items if caching is set only to
"Database cache."

Items with a status of 0 (safe IPs) are filtered from view, by default,
but can be viewed if you want to include them (just remove the filter).

You can also easily clone this view for a separate one that shows only
cleared IPs.

The IP addresses in the report include links to ProjectHoneyPot.org that
will allow you to see their current report on that IP.


KNOWN ISSUES
------------
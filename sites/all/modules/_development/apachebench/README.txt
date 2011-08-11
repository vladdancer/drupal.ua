$Id: README.txt,v 1.2 2009/03/19 21:30:19 neochief Exp $

ab - ApacheBench
Provided by http://vision-media.ca
Initial development: Tj Holowaychuk
Further development: Alexandr Shvets

------------------------------------------------------------------------------- 
INSTALLATION
------------------------------------------------------------------------------- 

1. Enable the module.
2. If you are using Windows, make sure that "Full ab utility path" is correct
install module's settings (admin/settings/ab).
3. Optionally, install the open_source_chart_api module for pretty charts.

------------------------------------------------------------------------------- 
PERMISSIONS
------------------------------------------------------------------------------- 

administer apachebench 
  - Control the automated ApacheBench cron tasks.

view apachebench reports
  - view reports from previous apachebench() invocations.

------------------------------------------------------------------------------- 
PUBLIC API
------------------------------------------------------------------------------- 

apachebench()
apachebench_clear_all()

------------------------------------------------------------------------------- 
FUTURE GOALS
------------------------------------------------------------------------------- 

- Implement open_source_chart_api charts for reporting, replacing tables
- Implement tablesort api
- Parse additional metrics from ab

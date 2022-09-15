/*
For this task
• When, map4() – same as map3() - creates the thread, it additionally assigns them a specific priority based on the
performance ratios in Task3, so that all threads finish at roughly the same time. Think how you would do that?
•a. You may need to run this task with escalated privileges in order to set process priorities. If so, please
indicate this in the report.
• Does reduce4() need to change from reduce3*( ?
• To get reasonably reliable performance data, you may need to pad out the input data with more duplicates.
• Can you tweak the thread performance so that they indeed finish at about the same time?
• Now compare the tweaked priorities with what you believe they should be. Do some research to discover how the
priority levels are related to speed.
• Describe all that you did in the report and what conclusions you came to.
Report: Document the following.
• Where are the threads spending most of their time?
• Can you come up with a big O representation? Justify your reasons.
• For the larger word lengths the string compare will also take longer. Is that significant?
• By checking the performance of the Task 3 threads, how close was the ratio of thread performance with the big O
expectation? For example if thread was O(n 2), then for larger n, a 3000-word thread should run 4 times as long as a
1500-word thread. So we have execution time and word count as two metrics for comparison*/
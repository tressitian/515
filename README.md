**Play with your sorting hat. Are all 10 questions important to create the sorting hat? If you were to remove some questions to improve user experience, which questions would you remove and justify your answer.**
I would remove the “Dream career” question. The options are too limited and may not reflect the full range of users’ aspirations. It also contributes less to sorting compared to questions about values or problem-solving styles.

**If you were to improve the sorting hat, what technical improvements would you make? Consider:
How could you improve the model's accuracy or efficiency?
What additional sensors or hardware could enhance the user experience?
Does decision tree remain suitable for your choice of new sensors? If yes, carefully justify your answer. If not, what ML model would you use and explain why.**
To improve the sorting hat’s accuracy, I would collect more training data and experiment with more advanced algorithms beyond the current decision tree. I would also consider integrating a heart rate sensor to capture physiological responses during questioning. This could add a new layer of emotional context—if someone’s heart rate changes significantly while answering certain questions, it may indicate deeper feelings or stress, which could influence the sorting result. While decision trees are simple and interpretable, they may not handle this kind of continuous sensor data effectively. In that case, I would switch to a model like a random forest or even an SVM, which can better handle mixed data types and more complex patterns.

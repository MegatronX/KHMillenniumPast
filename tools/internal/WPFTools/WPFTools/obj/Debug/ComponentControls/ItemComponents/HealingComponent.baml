   M S B A M L   `   `   `  ����O  Kmscorlib, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e0891&clr-namespace:System;assembly=mscorlibSystem  5       WPFTools@   :WPFTools.ComponentControls.ItemComponents.HealingComponent   5      W SPresentationCore, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35U QWPFToolkit, Version=3.5.40128.1, Culture=neutral, PublicKeyToken=31bf3856ad364e35^ ZWindowsFormsIntegration, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35H 9http://schemas.microsoft.com/winfx/2006/xaml/presentation      5      8x,http://schemas.microsoft.com/winfx/2006/xaml    5      Hmc;http://schemas.openxmlformats.org/markup-compatibility/2006    5      >d2http://schemas.microsoft.com/expression/blend/2008    5      4sys&clr-namespace:System;assembly=mscorlib    5      -   5        $!��HealingComponentUserControl��5   7     � 	Resources  5	      �� 5
   
      KeyHealingComponentTypes   �� Type" ��60   .s�5      ��Absolute��6#   ��5      AbsolutePercent��6*   ��5      RelativePercent��6*   5      �� 5   
   TypeTemplate  .R�5      �� $	��100��65   ��6   ��  �� XPath$ @type��65   5      .��5      �  � DataContext 5   
   �� 5       �� ElementName$! HealingComponentUserControl��6    �� Path$ RootComponentElement�6@   .+�5   
   �� -   5        $��ComponentOwner��5   i   $��39��60   $
��Left=�6<   $��0,52,0,0q�6W   $	��Top=�6   $	��232��6�   ��6   �� $ @name�� 5      �� 5      $! HealingComponentUserControl��6   $ ItemElement�6D   5      �� 5   
   -   5        $��	groupBox3��5   �   $��	Field Use��6H   $	��328��6[   $
��Left=�6h   $��	231,2,0,0q�6�   $	��Top=�6�   $	��220��6�    6   �� $ FieldHealingComponent��.��5      � .+�5      �� -   5        $��HPFieldUseGroup��5   r   $��HP Healing Component��6   $	��101��69   $
��Left=�6F   $��6,0,0,0q�6a   $	��Top=�6�   $	��192��6�   .��5      � .+�5       �� -   5        $��HPFieldHealingAmount��5       $��23��6E   $��Right=�6Q   $��0,16,6,0q�6m   $	��Top=�6�   $	��112��6�   ��6"   �� $ 
HP/@amount��6�   �� 5!      -   5        $��UseFieldHPHealing��5!   X   $	��Use��6#   $��16��61   $
��Left=�6=   $	��Top=�6q   6�   �� 5"      -   5        $��HPFielUseType��5"   �    �� SelectedValuePath$ @type��6#     HealingComponentTypes#��[ 6>   $��23��6s   $
��Left=�6   $��	62,49,0,0q�6�   $	��Top=�6�   $	��112��6   �� SelectedValue 6�   �� $
 HP/@�� �� Mode$ TwoWay=�6  �� 5#      -   5        $��label2��5#   j   $��Amount��6    $��28��61   $
��Left=�6=   $��6,14,0,0q�6X   $	��Top=�6x   �� 5$      -	   5        $��label3��5$   h   $
��Type��6    $��28��6/   $
��Left=�6;   $��6,44,0,0q�6V   $	��Top=�6v   5%      5&      �� 5'      -
   5        $��SPHealingComponent��5'   t   $��SP Healing Component��6   $	��101��69   $
��Left=�6F   $��	6,199,0,0q�6a   $	��Top=�6�   $	��192��6�   .��5(      � .+�5)      �� -   5        $��textBox4��5)   \   $��23��6"   $��Right=�6.   $��0,16,6,0q�6J   $	��Top=�6�   $	��112��6�   ��6l   �� $ 
SP/@amount��6�   �� 5*      -   5        $��UseFieldSPHealing��5*   X   $	��Use��6#   $��16��61   $
��Left=�6=   $	��Top=�6q   6�   �� 5+      -   5        $��SPFieldUseType��5+   �   #��[ 6#   $��23��6�   $
��Left=�6�   $��	62,49,0,0q�6�   $	��Top=�6�   $	��112��6�   	 �� SelectedItem	 6X   �� $ SP/@type��$ TwoWay=�6�   �� 5,      -   5        $��label9��5,   j   $��Amount��6    $��28��61   $
��Left=�6=   $��6,14,0,0q�6X   $	��Top=�6x   �� 5-      -   5        $��label10��5-   h   $
��Type��6    $��28��6/   $
��Left=�6;   $��6,44,0,0q�6V   $	��Top=�6w   5.      5/      �� 50      -   5        $��	groupBox2��50   t   $��MP Healing Component��6   $	��101��69   $
��Left=�6F   $��	6,101,0,0q�6a   $	��Top=�6�   $	��192��6�   .��51      � -   5        $��MPHealingComponentBox��51      .+�52      �� -   5        $��textBox5��52   \   $��23��6"   $��Right=�6.   $��0,16,6,0q�6J   $	��Top=�6�   $	��112��6�   ��6l   �� $ 
MP/@amount��6�   �� 53      -   5        $��UseFieldMPHealing��53   X   $	��Use��6#   $��16��61   $
��Left=�6=   $	��Top=�6q   6�   �� 54      -   5        $��MPFieldUseType��54   �   #��[ 6#   $��23��6�   $
��Left=�6�   $��	62,49,0,0q�6�   $	��Top=�6�   $	��112��6�   	 6X   �� $ MP/@type��$ TwoWay=�6�   �� 55      -   5        $��label12��55   j   $��Amount��6    $��28��61   $
��Left=�6=   $��6,14,0,0q�6X   $	��Top=�6y   �� 56      -   5        $��label13��56   h   $
��Type��6    $��28��6/   $
��Left=�6;   $��6,44,0,0q�6V   $	��Top=�6w   57      58      59      5:      �� 5;   
   -   5        $��BattleUseGroupBox��5;   �   $��
Battle Use��6I   $	��328��6]   $
��Left=�6j   $��	457,2,0,0q�6�   $	��Top=�6�   $	��220��6�    6   �� $ BattleHealingComponent��.��5<      � .+�5=      �� -   5        $��HPBattleUseGroupBox��5=   r   $��HP Healing Component��6   $	��101��69   $
��Left=�6F   $��6,0,0,0q�6a   $	��Top=�6�   $	��192��6�   .��5>      � .+�5?      �� -   5        $��textBox1��5?   \   $��23��6"   $��Right=�6.   $��0,16,6,0q�6J   $	��Top=�6�   $	��112��6�   ��6l   �� $ 
HP/@amount��6�   �� 5@      -   5        $��UseBattleHPHealing��5@   X   $	��Use��6#   $��16��61   $
��Left=�6=   $	��Top=�6r   6�   �� 5A      -   5        $��HPBattleUseType��5A   �   $ @type��6#   #��[ 6>   $��23��6s   $
��Left=�6   $��	62,49,0,0q�6�   $	��Top=�6�   $	��112��6   6�   �� $ HP/@type��6  �� 5B      -   5        $��label4��5B   j   $��Amount��6    $��28��61   $
��Left=�6=   $��6,14,0,0q�6X   $	��Top=�6x   �� 5C      -   5        $��label5��5C   h   $
��Type��6    $��28��6/   $
��Left=�6;   $��6,44,0,0q�6V   $	��Top=�6v   5D      5E      �� 5F      -   5        $��	groupBox6��5F   t   $��SP Healing Component��6   $	��101��69   $
��Left=�6F   $��	6,199,0,0q�6a   $	��Top=�6�   $	��192��6�   .��5G      � .+�5H      �� -   5        $��textBox3��5H   \   $��23��6"   $��Right=�6.   $��0,16,6,0q�6J   $	��Top=�6�   $	��112��6�   ��6l   �� $ 
SP/@amount��6�   �� 5I      -    5        $��UseBattleSPHealing��5I   X   $	��Use��6#   $��16��61   $
��Left=�6=   $	��Top=�6r   6�   �� 5J      -!   5        $��SPBattleUseType��5J   �   #��[ 6#   $��23��6�   $
��Left=�6�   $��	62,49,0,0q�6�   $	��Top=�6�   $	��112��6�   	 6X   �� $ SP/@type��6�   �� 5K      -"   5        $��label7��5K   j   $��Amount��6    $��28��61   $
��Left=�6=   $��6,14,0,0q�6X   $	��Top=�6x   �� 5L      -#   5        $��label8��5L   h   $
��Type��6    $��28��6/   $
��Left=�6;   $��6,44,0,0q�6V   $	��Top=�6v   5M      5N      �� 5O      -$   5        $��	groupBox7��5O   t   $��MP Healing Component��6   $	��101��69   $
��Left=�6F   $��	6,101,0,0q�6a   $	��Top=�6�   $	��192��6�   .��5P      � -%   5        $��grid1��5P      .+�5Q      �� -&   5        $��textBox2��5Q   \   $��23��6"   $��Right=�6.   $��0,16,6,0q�6J   $	��Top=�6�   $	��112��6�   ��6l   �� $ 
MP/@amount��6�   �� 5R      -'   5        $��UseBattleMPHealing��5R   X   $	��Use��6#   $��16��61   $
��Left=�6=   $	��Top=�6r   6�   �� 5S      -(   5        $��MPBattleUseType��5S   �   #��[ 6#   $��23��6�   $
��Left=�6�   $��	62,49,0,0q�6�   $	��Top=�6�   $	��112��6�   	 6X   �� $ MP/@type��6�   �� 5T      -)   5        $��label1��5T   j   $��Amount��6    $��28��61   $
��Left=�6=   $��6,14,0,0q�6X   $	��Top=�6x   �� 5U      -*   5        $��label6��5U   h   $
��Type��6    $��28��6/   $
��Left=�6;   $��6,44,0,0q�6V   $	��Top=�6v   5V      5W      5X      5Y      �� 5Z   
   -+   5        $��label11��5Z   �   ���	#FF3EA76C$��Healing Component��6'   $
��Bold"�6C   
�������$��28��6h   $
��Left=�6t   $��0,2,0,0q�6�   $	��Top=�6�   $	��232��6�   5[      5\      
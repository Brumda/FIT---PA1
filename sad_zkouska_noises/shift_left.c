TNODE *shiftLeft(TNODE *a, unsigned int shift)
{
    if (a == NULL)
    {
        return NULL;
    }
    TNODE *tmp = a;
    while (tmp)
    {
        char digit = tmp->m_Digit;
        if ((digit < '0' || digit > '9') && (digit < 'a' || digit > 'f'))
        {
            return NULL;
        }
        if (digit == '0' && tmp->m_Next == NULL)
        {
            return NULL;
        }
        tmp = tmp->m_Next;
    }
    tmp = a;
    int nextAdd = 0;
    TNODE *newHead = NULL;
    TNODE *prev = NULL;
    char curDigit;
    while (tmp)
    {
        char charDigit = tmp->m_Digit;
        int numDigit = 0;
        if (charDigit >= '0' && charDigit <= '9')
        {
            numDigit = charDigit - '0';
        }
        else
        {
            numDigit = charDigit - 'a' + 10;
        }
        int shiftNum = numDigit * pow(2, shift) + nextAdd;
        nextAdd = shiftNum / pow(2, 4);
        int curNum = shiftNum - nextAdd * pow(2, 4);
        if (curNum < 10)
        {
            curDigit = '0' + curNum;
        }
        else
        {
            curNum -= 10;
            curDigit = 'a' + curNum;
        }
        if (newHead == NULL)
        {
            newHead = (TNODE *)malloc(sizeof(*newHead));
            newHead->m_Digit = curDigit;
            newHead->m_Next = NULL;
            prev = newHead;
        }
        else
        {
            TNODE *n = (TNODE *)malloc(sizeof(*n));
            n->m_Digit = curDigit;
            n->m_Next = NULL;
            prev->m_Next = n;
            prev = n;
        }
        tmp = tmp->m_Next;
    }
    if (nextAdd > 0)
    {
        if (nextAdd < 10)
        {
            curDigit = '0' + nextAdd;
        }
        else
        {
            nextAdd -= 10;
            curDigit = 'a' + nextAdd;
        }
        TNODE *n = (TNODE *)malloc(sizeof(*n));
        n->m_Digit = curDigit;
        n->m_Next = NULL;
        prev->m_Next = n;
    }
    return newHead;
}
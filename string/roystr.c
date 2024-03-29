#include "roystr.h"

char *
roy_str_to_lower(char * str) {
  char * pstr = str;
  while ((*pstr = tolower(*pstr)) != '\0') {
    pstr++;
  }
  return str;
}

char *
roy_str_to_upper(char * str) {
  char * pstr = str;
  while ((*pstr = toupper(*pstr)) != '\0') {
    pstr++;
  }
  return str;
}

char *
roy_str_reverse(char * str) {
  char * pstr_head = str;
  char * pstr_tail = str + strlen(str) - 1;
  while (pstr_tail > pstr_head) {
    char temp = *pstr_head;
    *pstr_head++ = *pstr_tail;
    *pstr_tail-- = temp;
  }
  return str;
}

char *
roy_str_unique_char(char * str,
                    int    ch) {
  // temp_str: a temporary-stored string.
  ROY_STR(temp_str, strlen(str))
  // a pointer to the real temp_str.
  char * ptemp_str = temp_str;
  // a pointer to the real str.
  char * pstr = str;
  // stand when the first 'ch' is tracked, lay down when repeating 'ch's end.
  bool flag = false;
  while (*pstr != '\0') {
    if (!flag && *pstr == ch) {
      flag = true;
      *ptemp_str++ = *pstr++;
    } else if (!flag && *pstr != ch) {
      *ptemp_str++ = *pstr++;
    } else if (flag && *pstr == ch) {
      pstr++;
    } else { // (flag && *src != ch)
      flag = false;
      *ptemp_str++ = *pstr++;
    }
  }
  strcpy(str, temp_str);
  return str;
}

char *
roy_str_replace_all(char       * str,
                    const char * old_sub,
                    const char * new_sub) {
  // temp_str: a temporary-stored string.
  ROY_STR(temp_str, strlen(str))
  // a pointer to the real temp_str.
  char * ptemp_str = temp_str;
  // a pointer to the real str.
  char * pstr;
  // a pointer to the beginning of a matched substring.
  pstr = str;
  char * pmatch_begin;
  while ((pmatch_begin = strstr(pstr, old_sub))) {
    strncat(ptemp_str, pstr, pmatch_begin - pstr);
    strcat(ptemp_str, new_sub);
    pstr = pmatch_begin + strlen(old_sub);
  }
  strcat(temp_str, pstr);
  strcpy(str, temp_str);
  return str;
}


char *
roy_str_replace_index(char       * str,
                      size_t       old_sub_pos,
                      size_t       old_sub_len,
                      const char * new_sub) {
  ROY_STR(temp_str, strlen(str) + strlen(new_sub) - old_sub_len)
  strncpy(temp_str, str, old_sub_pos);
  strcat(temp_str, new_sub);
  strcat(temp_str, str + old_sub_pos + old_sub_len);
  strcpy(str, temp_str);
  return str;
}

char *
roy_str_replace_between(char       * str,
                        const char * pattern_head,
                        const char * pattern_tail,
                        const char * new_sub) {
  char * phead = str;
  bool flag = false;
  while ((phead = strstr(str, pattern_head))) {
    if (flag == true) {
      char * ptail = strstr(phead, pattern_tail);
      roy_str_replace_index(str,
                            phead - str,
                            ptail - phead + strlen(pattern_tail),
                            new_sub);
      flag = false;  
    } else {
      flag = true;
    }
  }
  return str;
}

char *
roy_str_replace_all_char(char * str,
                         int    old_ch,
                         int    new_ch) {
  char * pstr = str;
  while (*pstr != '\0') {
    if (*pstr == old_ch) {
      *pstr = new_ch;
    }
    pstr++;
  }
  return str;
}

char *
roy_str_replace_all_char_if(char  * str,
                            int  (* checker)(int),
                            int     new_ch) {
  char * pstr = str;
  while (*pstr != '\0') {
    if (checker(*pstr)) {
      *pstr = new_ch;
    }
    pstr++;
  }
  return str;
}

char *
roy_str_line(char       * line_content,
             const char * str,
             size_t       line_number) {
  while ((line_number-- > 1) && strchr(str, '\n')) {
    str = strchr(str, '\n') + 1; // excludes the '\n' right before the line.
  }
  const char * str_tail = strchr(str, '\n');
  if (!str_tail) {
    strcpy(line_content, str);
  } else {
    strncpy(line_content, str, str_tail - str);
  }
  return line_content;
}

char *
roy_str_trim_line(char * str) {
  char * pstr_tail = str + strlen(str);
  while (str < pstr_tail && isblank(*(pstr_tail - 1))) {
    pstr_tail--;
  }
  *pstr_tail = '\0';
  return str;
}

char *
roy_str_trim(char * str) {
  ROY_STR(temp_str, strlen(str))
  for (size_t i = 1; i <= roy_str_count_line(str); i++) {
    ROY_STR(cur_line, roy_str_line_length(str, i))
    roy_str_line(cur_line, str, i);
    roy_str_trim_line(cur_line);
    if (strlen(cur_line) != 0) { 
      strcat(temp_str, "\n");
      strcat(temp_str, cur_line);
    }
  }
  strcpy(str, temp_str + 1);
  return str;
}

char *
roy_str_fill_char(char   * dest,
                  int      ch,
                  size_t   count) {
  size_t i = 0;
  for (; i != count; i++) {
    *(dest + i) = ch;
  }
  *(dest + i) = '\0';
  return dest;
}

static char *
sequence(char * dest,
         int    front_ch,
         int    back_ch) {
  char * pdest = dest;
  while (front_ch <= back_ch) {
    *pdest++ = front_ch++;
  }
  *pdest = '\0';
  return dest;
}

char *
roy_str_fill_sequence(char       * dest,
                      const char * pattern) {
  typedef enum { LEFT, MIDDLE, RIGHT } Flag;
  Flag flag = 0;
  char * pdest = dest;
  while (*pattern != '\0') {
    if (flag == LEFT && isprint(*pattern)) {
      flag = MIDDLE;
    } else if (flag == MIDDLE && *pattern == '-') {
      flag = RIGHT;
    } else if (flag == RIGHT && isprint(*pattern)) {
      char buf[R_BUF_SIZE] = "\0";
      strcat(dest, sequence(buf, *(pattern - 2), *pattern));
      pdest += strlen(buf);
      flag = LEFT;
    } else if (flag == MIDDLE && isprint(*pattern)) {
      *pdest++ = *(pattern - 1);
    }
    pattern++;
  }
  while (flag > 0) {
    *pdest++ = *(pattern - flag--);
  }
  *pdest = '\0';
  return dest;
}

char *
roy_str_detab(char   * str,
              size_t   tab_size) {
  char * pstr = str;
  size_t tab_marker = 0;
  while (*pstr != '\0') {
    if (*pstr == '\t') {
      ROY_STR(rpt_str, tab_size)
      size_t rpt_count = tab_size - tab_marker % tab_size;
      roy_str_fill_char(rpt_str, ' ', rpt_count);
      roy_str_replace_index(str, pstr - str, 1, rpt_str);
      tab_marker += rpt_count - 1;
      pstr += rpt_count - 1;
    } else if (*pstr == '\n') {
      tab_marker = 0;
      pstr++;
    } else {
      tab_marker++;
      pstr++;
    }
  }
  return str;
}

char *
roy_str_entab(char   * str,
              size_t   tab_size) {
  char * pstr = str;
  size_t pos = 1;
  while (*pstr != '\0') {
    if (*pstr == ' ' && pos % tab_size == 0) {
      char * pblank = pstr;
      while (*pblank == ' ') {
        pblank--;
      }
      roy_str_replace_index(str, pblank - str + 1, pstr - pblank, "\t");
      pos += pstr - pblank - 1;
    }
    if (*pstr == '\n') {
      pos = 0;
    }
    pstr++;
    pos++;
  }
  return str;
}


char *
roy_str_fold_line(char   * str,
                  size_t   line_width) {
  char * pstr = str;
  while (strlen(pstr) > line_width) {    
    pstr += line_width - 1;
    if(isblank(*(pstr + 1))) {
      while (isblank(*(pstr++ + 1))) {  }
      *(pstr - 1) = '\n';
    } else {
      if (!isblank(*pstr)) {
        while (!isblank(*(pstr-- - 1))) {  }
      }
      *pstr++ = '\n';
    }
  }
  return str;
}

char *
roy_str_fold(char   * str,
             size_t   line_width) {
  ROY_STR(temp_str, strlen(str))
  for (size_t i = 1; i <= roy_str_count_line(str); i++) {
    ROY_STR(cur_line, roy_str_line_length(str, i))
    roy_str_line(cur_line, str, i);
    roy_str_fold_line(cur_line, line_width);
    strcat(temp_str, "\n");
    strcat(temp_str, cur_line);
  } 
  strcpy(str, temp_str + 1);
  return str;
}

char *
roy_str_squeeze(char       * str,
                const char * set) {
  int i = 0, j = 0;
  while (*(str + i) != '\0') {
    if (strchr(set, *(str + i))) { /* current character belongs to 'set' */
      i++;
    } else {
      *(str + j++) = *(str + i++);
    }
  }
  *(str + j) = '\0';
  return str;
}

size_t
roy_str_count_char(const char * str,
                   int          ch) {
  size_t count = 0;
  while (*str != '\0') {
    if (*str++ == ch) {
      count ++;
    }
  }
  return count;
}

size_t
roy_str_count_char_if(const char  * str, 
                      int        (* checker)(int)) {
  size_t count = 0;
  while (*str != '\0') {
    if (checker(*str++)) {
      count++;
    }
  }
  return count;
}

size_t
roy_str_count_substring(const char * str,
                        const char * sub,
                        bool         sensibility) {
  size_t count = 0;
  const char * pstr;
  const char * psub;
  ROY_STR(lower_str, strlen(str))
  ROY_STR(lower_sub, strlen(sub))

  if (sensibility) {
    pstr = str;
    psub = sub;
  } else {
    strcpy(lower_str, str);
    roy_str_to_lower(lower_str);
    pstr = lower_str;

    strcpy(lower_sub, sub);
    roy_str_to_lower(lower_sub);
    psub = lower_sub;
  }

  char * pmatch_begin;
  while ((pmatch_begin = strstr(pstr, psub))) {
    count++;
    pstr = pmatch_begin + strlen(psub);
  } 
  return count;
}

size_t
roy_str_count_word(const char * str) {
  const char * pstr = str;
  size_t count = 0;
  bool flag = false;
  do {
    if (!flag && isalnum(*pstr)) {
      flag = true;
    } else if (flag && !isalnum(*pstr)) {
      flag = false;
      count++;
    }
  } while (*pstr++ != '\0');
  return count;
}

size_t
roy_str_count_word_if(const char * str,
                      size_t       length) {
  bool flag = false;
  size_t length_cur = 0;
  size_t count_cur = 0;

  do {
    if (!flag && isalnum(*str)) {
      flag = true;
      length_cur++;
    } else if (flag && isalnum(*str)) {
      length_cur++;
    } else if (flag && !isalnum(*str)) {
      flag = false;
      if (length_cur == length) {
        count_cur++;
      }
      length_cur = 0;
    } // (!flag && !isalnum(*pstr)) does nothing
    str++;
  } while (*str != '\0');
  
  return count_cur;
}

size_t
roy_str_count_line(const char * str) {
  size_t str_length = strlen(str);
  size_t count = roy_str_count_char(str, '\n');
  if (str_length != 0 && *(str + str_length - 1) != '\n') {
    // last char is not '\n', but that line still needs to be counted.
    count++;
  }
  return count;
}

size_t
roy_str_line_length(const char * str,
                    size_t       line_number) {
  while ((line_number-- > 1) && strchr(str, '\n')) {
    str = strchr(str, '\n') + 1; // excludes the '\n' right before the line.
  }
  const char * str_tail = strchr(str, '\n');
  if (!str_tail) {
    return strlen(str);
  } else {
    return str_tail - str;
  }
}

int
roy_str_break_index(const char * str,
                    const char * set) {
  int pos = 0;
  while (*(str + pos) != '\0' && !strchr(set, *(str + pos))) {
    pos++;
  }
  return pos;
}

char *
roy_str_read_from_file(char       * dest,
                       const char * path) {
  FILE * fp = fopen(path, "r");
  ROY_STR(buf, R_BUF_SIZE)
  fgets(buf, R_BUF_SIZE, fp);
  strcpy(dest, buf);
  while (fgets(buf, R_BUF_SIZE, fp)) {
    strcat(dest, buf);
  }
  fclose(fp);
  return dest;
}

int
roy_str_append_to_file(const char * src,
                       const char * path) {
  FILE * fp = fopen(path, "a+");
  int ret = fputs(src, fp);
  fclose(fp);
  return ret;
}

int
roy_str_write_to_file(const char * src,
                      const char * path) {
  FILE * fp = fopen(path, "w+");
  int ret = fputs(src, fp);
  fclose(fp);
  return ret;
}
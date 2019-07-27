#include "../include/roystr.h"

RoyStr
roy_str_to_lower(RoyStr str) {
  char * pstr = str;
  while ((*pstr = tolower(*pstr)) != '\0') {
    pstr++;
  }
  return str;
}

RoyStr
roy_str_to_upper(RoyStr str) {
  char * pstr = str;
  while ((*pstr = toupper(*pstr)) != '\0') {
    pstr++;
  }
  return str;
}

RoyStr
roy_str_reverse(RoyStr str) {
  char * pstr_head = str;
  char * pstr_tail = str + strlen(str) - 1;
  while (pstr_tail > pstr_head) {
    char temp = *pstr_head;
    *pstr_head++ = *pstr_tail;
    *pstr_tail-- = temp;
  }
  return str;
}

RoyStr
roy_str_unique_char(RoyStr str,
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

// TODO: the function needs to be character insensible.
RoyStr
roy_str_replace_all(RoyStr str,
                       RoyStrLiteral old_sub,
                       RoyStrLiteral new_sub,
                       bool         sensibility) {
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


RoyStr
roy_str_replace_index(RoyStr  str,
                         size_t       old_sub_pos,
                         size_t       old_sub_len,
                         RoyStrLiteral new_sub) {
  ROY_STR(temp_str, strlen(str) + strlen(new_sub) - old_sub_len)
  strncpy(temp_str, str, old_sub_pos);
  strcat(temp_str, new_sub);
  strcat(temp_str, str + old_sub_pos + old_sub_len);
  strcpy(str, temp_str);
  return str;
}

RoyStr
roy_str_replace_between(RoyStr  str,
                           RoyStrLiteral pattern_head,
                           RoyStrLiteral pattern_tail,
                           RoyStrLiteral new_sub) {
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

RoyStr
roy_str_replace_all_char(RoyStr str,
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

RoyStr
roy_str_replace_all_char_if(RoyStr  str,
                               int  (* condition)(int),
                               int     new_ch) {
  char * pstr = str;
  while (*pstr != '\0') {
    if (condition(*pstr)) {
      *pstr = new_ch;
    }
    pstr++;
  }
  return str;
}

RoyStr
roy_str_line(RoyStr  line_content,
                RoyStrLiteral str,
                size_t       line_number) {
  while ((line_number-- > 1) && strchr(str, '\n')) {
    str = strchr(str, '\n') + 1; // excludes the '\n' right before the line.
  }
  RoyStrLiteral str_tail = strchr(str, '\n');
  if (!str_tail) {
    strcpy(line_content, str);
  } else {
    strncpy(line_content, str, str_tail - str);
  }
  return line_content;
}

RoyStr
roy_str_trim_line(RoyStr str) {
  char * pstr_tail = str + strlen(str);
  while (str < pstr_tail && isblank(*(pstr_tail - 1))) {
    pstr_tail--;
  }
  *pstr_tail = '\0';
  return str;
}

RoyStr
roy_str_trim(RoyStr str) {
  ROY_STR(temp_str, strlen(str))
  for (int i = 1; i <= roy_str_count_line(str); i++) {
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

RoyStr
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

RoyStr
roy_str_fill_sequence(RoyStr  dest,
                         RoyStrLiteral pattern) {
  bool flag = false; // is current char in sequence
  while (*pattern != '\0') {
    pattern++;
  }
  return "";
}

RoyStr
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

RoyStr
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


RoyStr
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

RoyStr
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

RoyStr
roy_str_squeeze(RoyStr  str,
                   RoyStrLiteral set) {
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
roy_str_count_char(RoyStrLiteral str,
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
roy_str_count_char_if(RoyStrLiteral  str, 
                         int        (* condition)(int)) {
  size_t count = 0;
  while (*str != '\0') {
    if (condition(*str++)) {
      count++;
    }
  }
  return count;
}

size_t
roy_str_count_substring(RoyStrLiteral str,
                           RoyStrLiteral sub,
                           bool         sensibility) {
  size_t count = 0;
  RoyStrLiteral pstr;
  RoyStrLiteral psub;
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

  RoyStrLiteral pmatch_begin;
  while ((pmatch_begin = strstr(pstr, psub))) {
    count++;
    pstr = pmatch_begin + strlen(psub);
  } 
  return count;
}

size_t
roy_str_count_word(RoyStrLiteral str) {
  RoyStrLiteral pstr = str;
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
roy_str_count_word_if(RoyStrLiteral str,
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
roy_str_count_line(RoyStrLiteral str) {
  size_t str_length = strlen(str);
  size_t count = roy_str_count_char(str, '\n');
  if (str_length != 0 && *(str + str_length - 1) != '\n') {
    // last char is not '\n', but that line still needs to be counted.
    count++;
  }
  return count;
}

size_t
roy_str_line_length(RoyStrLiteral str,
                       size_t       line_number) {
  while ((line_number-- > 1) && strchr(str, '\n')) {
    str = strchr(str, '\n') + 1; // excludes the '\n' right before the line.
  }
  RoyStrLiteral str_tail = strchr(str, '\n');
  if (!str_tail) {
    return strlen(str);
  } else {
    return str_tail - str;
  }
}

int
roy_str_break_index(RoyStrLiteral str,
                       RoyStrLiteral set) {
  int pos = 0;
  while (*(str + pos) != '\0' && !strchr(set, *(str + pos))) {
    pos++;
  }
  return pos;
}

RoyStr
roy_str_read_from_file(RoyStr  dest,
                          RoyStrLiteral path) {
  FILE * fp = fopen(path, "r");
  ROY_STR(buf, STRING_CAPACITY)
  fgets(buf, STRING_CAPACITY, fp);
  strcpy(dest, buf);
  while (fgets(buf, STRING_CAPACITY, fp)) {
    strcat(dest, buf);
  }
  fclose(fp);
  return dest;
}

int
roy_str_append_to_file(RoyStrLiteral src,
                          RoyStrLiteral path) {
  FILE * fp = fopen(path, "a+");
  int ret = fputs(src, fp);
  fclose(fp);
  return ret;
}

int
roy_str_write_to_file(RoyStrLiteral src,
                         RoyStrLiteral path) {
  FILE * fp = fopen(path, "w+");
  int ret = fputs(src, fp);
  fclose(fp);
  return ret;
}